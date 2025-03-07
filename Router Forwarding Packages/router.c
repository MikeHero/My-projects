#include "queue.h"
#include "skel.h"

struct arp_entry *arp_table;
struct route_table_entry *r_table;
int arp_table_len;
int r_table_len;

struct route_table_entry *get_best_route(struct in_addr dest_ip) 
{
    struct route_table_entry *result = NULL;
    uint32_t mask_max = 0; 

    for(int i = 0; i < r_table_len; i++) 
    {
        uint32_t dest_ip_masked = dest_ip.s_addr & r_table[i].mask;
        uint32_t network_ip = r_table[i].prefix;
        if((dest_ip_masked == network_ip) && (mask_max <= r_table[i].mask))
        {
                result = &r_table[i];
                mask_max = r_table[i].mask;
        }
    }
    return result;
}

struct arp_entry *get_arp_entry(struct in_addr dest_ip) 
{

    for(int i = 0; i < arp_table_len; i++)
    {
            if(arp_table[i].ip == dest_ip.s_addr)
            {
                return &arp_table[i];
            }
    }

    return NULL;
    
}

// crescator dupa prefix, crescator dupa masca
int fcmp(struct route_table_entry a, struct route_table_entry b)
{
	if( a.prefix < b.prefix)
		return 1;
	else 
	{	
		if( (a.prefix == b.prefix) && ( a.mask < b.mask ) )
			return 1;
	}
	return -1;
}

void order_route_table(struct route_table_entry* v, int n)
{
	struct route_table_entry aux;
	int i , j;
	for( i = 0; i < n; i++)
		for( j = i + 1; j < n; j++)
		{
			if( fcmp (v[i], v[j] ) < 0 )
			{	
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
}

struct route_table_entry *get_best_route_efficient(struct in_addr dest_ip)
{
	int inc = 0;
	int sf = r_table_len - 1;
	int mj;
	while( inc <= sf)
	{
		mj = (inc + sf ) / 2;
		uint32_t dest_ip_masked = dest_ip.s_addr & r_table[mj].mask;
		if( r_table[mj].prefix == dest_ip_masked)
		{	
			// ordonat crescator si dupa masca
			while( (dest_ip.s_addr & r_table[mj + 1].mask) == r_table[mj + 1].prefix  )
				mj++;
			// dupa ce am facut un match, cu cat merg mai jos si se pastreaza matchul, masca e mai mare
			// cand nu mai e match, masca este maxima, ca este ordonata crescator
			return &r_table[mj];
		}
		else
		{
			if( dest_ip_masked > r_table[mj].prefix) // caut in dreapta, ca este ordonat crescator
			{
				inc = mj;
			}
			else
			{
				// caut in stanga
				sf = mj;
			}
		}
	}
	return NULL;
} 


int main(int argc, char *argv[])
{
	packet m;
	int rc;

	// Do not modify this line
	init(argc - 2, argv + 2);

	r_table = malloc(sizeof(struct route_table_entry) * 100000);
	DIE(r_table == NULL, "eroare alocare memorie r_table");

	arp_table = malloc(sizeof(struct  arp_entry) * 6);
	DIE(arp_table == NULL, "eroare alocare memorie arp_table");

	// Read the static routing table and the MAC table 
	r_table_len = read_rtable(argv[1], r_table);
	arp_table_len = parse_arp_table("arp_table.txt", arp_table);

	order_route_table(r_table, r_table_len);
	
	fprintf(stderr, "am pornit\n");
	while (1) 
	{
		
		rc = get_packet(&m);
		DIE(rc < 0, "get_packet");
		// TODO 
			

		struct ether_header *eth_hdr = (struct ether_header *) m.payload;
		
		if( eth_hdr->ether_type ==  htons(ETHERTYPE_IP) ) // 0x0800 macro
		{
			struct iphdr *ip_hdr = (struct iphdr *)(m.payload + sizeof(struct ether_header));

			// TODO 4: Check the checksum as required by IPv4  
			uint16_t old_checksum = ip_hdr->check;
			ip_hdr->check = 0;
			uint16_t my_checksum = ip_checksum(ip_hdr, sizeof(struct iphdr));
			if( old_checksum != my_checksum)
			{	
				fprintf(stderr, "Checksumuri nepotrivite, ii dau drop\n");
				continue; // drop
			}

			// TODO 5: Check TTL >= 1 
			if( (*ip_hdr).ttl <= 1)
			{	
				fprintf(stderr, "TTL mai mic ca 1 error, ii dau drop\n");
				continue; //drop 
			}





			struct in_addr dest_ip;
			dest_ip.s_addr = ip_hdr->daddr;
			
			struct route_table_entry* best_matching_route = get_best_route( dest_ip );
			if( !best_matching_route) 
			{	
				fprintf(stderr, "matching_route nu am gasit\n");
				continue;
			}
			// DIFERIT de NULL
			struct arp_entry* matching_neighbour = get_arp_entry(dest_ip);
			if( ! matching_neighbour)
			{	
				fprintf(stderr, "adresa mac a lui next hop nu am gasit\n");
				continue;
				
			}


			ip_hdr->ttl--;
			ip_hdr->check = 0;
			ip_hdr->check = ip_checksum(ip_hdr, sizeof(struct iphdr));

			memcpy(eth_hdr->ether_dhost, matching_neighbour->mac, 6);

			get_interface_mac(best_matching_route->interface, eth_hdr->ether_shost);
			m.interface = best_matching_route->interface;
			fprintf(stderr, "interfata %d\n", m.interface);
			send_packet(&m);
			fprintf(stderr, "packet sent\n");
		}
		else
		{
			//nu este pachet IP
			continue;
		}




	}
}
