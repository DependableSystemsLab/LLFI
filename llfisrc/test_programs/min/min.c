#include<stdio.h>
main(argc, argv)
    int argc;
    char *argv[];
{
        int arr[5],min,i;
        //printf("%p\n", arr);
		for(i=0;i<5;i++)
			arr[i] = atoi(argv[i+1]);
		min=arr[0];
		for(i=1;i<5;i++)
			if(min > arr[i])
				min = arr[i];
		printf("Min is:%d",min);
		return 0;
}

