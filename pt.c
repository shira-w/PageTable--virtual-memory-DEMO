#include "os.h" 
#include "malloc.h"
#include "stdlib.h"
#include "stdio.h"
#include <assert.h>
#include <err.h>
#include <sys/mman.h>
//help function: chek mapping and return the next adress
uint64_t IsMapping(uint64_t tableAddress,uint64_t index)
{
	uint64_t* table=(uint64_t*)tableAddress;
	uint64_t entry= table[index];
	if((entry&0x1)==0)
		return NO_MAPPING;
	else
		return entry;
}
//help function: perform mapping
uint64_t Mapping(uint64_t tableAddress,uint64_t index,uint64_t ppn,int treatppn)
{
	    uint64_t* table=(uint64_t*)tableAddress;
		if(treatppn==0)//regular mapping
		{
			uint64_t entry=alloc_page_frame();
			entry=(uint64_t)phys_to_virt(entry<<12);
			entry=(entry|0x1);
			table[index]=entry;
			return entry;
		}
		else//ppn mapping
		{
			if(ppn==NO_MAPPING)
			{
				table[index]>>=1;//zero the valid bit in ppn
				table[index]<<=1;
				return NO_MAPPING;
			}
			else
			{
			uint64_t ppnFinal=ppn;
			ppnFinal=(ppnFinal<<12);
			ppnFinal=(ppnFinal|0x1);
			table[index]=ppnFinal;
			return ppnFinal;
			}
		}
}
void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn)//64 bits
{
	pt=(uint64_t)phys_to_virt(pt<<12);
	vpn=vpn>>12;
	uint64_t isolationBits=36;
	uint64_t tableAddress= pt;
	uint64_t index;
	for (int i = 2; i <=5; i++)
	{
		index=(vpn>>isolationBits);
		index=(index&0x1FF);
		uint64_t temp=tableAddress;
		tableAddress=IsMapping(tableAddress,index);
		if(tableAddress==NO_MAPPING)
		{
			if(ppn==NO_MAPPING)
				return;
			tableAddress=Mapping(temp,index,ppn,0);
		}
		isolationBits-=9;
	}
	Mapping(tableAddress,index,ppn,1);
}
uint64_t page_table_query(uint64_t pt, uint64_t vpn)
{
	vpn=vpn>>12;
	pt=(uint64_t)phys_to_virt(pt<<12);
	uint64_t isolationBits=36;
	uint64_t tableAddress=pt;
	uint64_t index;
	for(int i=2;i<=5;i++)
	{
		index=vpn>>isolationBits;
		index=(index&0x1FF);
		tableAddress=IsMapping(tableAddress,index);
		if(tableAddress==NO_MAPPING)
			return NO_MAPPING;
		isolationBits-=9;
	}
	uint64_t isMap=IsMapping(tableAddress,index);
	if(isMap==NO_MAPPING)//tableAddress is the ppn
			return NO_MAPPING;
	else
	{
	 isMap=isMap>>12;
	 return isMap;
	}

}


