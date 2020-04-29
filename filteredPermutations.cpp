

#include <iostream>
#include <algorithm>

using namespace std;


int main()
{
    int arry[4] = {2,3,4,5};

    do 
    {	
    	bool canDo = true;
    	for(int i=0;i<3;i++)
    	{
    		if ( (arry[i] == 2) || (arry[i] == 3) )
    		{
    			if( (arry[i+1] == 2) || (arry[i+1] == 3) )
    			{
    				canDo = false;
    				break;
    			}
    			
    		}
    	}
    	if(canDo)
    	{
    		std::cout << arry[0] << ' ' << arry[1] << ' ' << arry[2] <<' '<< arry[3] << '\n';
    	}
        
    } 
    while ( std::next_permutation(arry,arry+4) );

    return 0;
}