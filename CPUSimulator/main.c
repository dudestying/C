#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void firstComeFS(int detailed,int verbose);
void roundRobin(int detailed,int verbose,int amount);

int main(int argc, char **argv) 
{
    int amount=0;
	int option=0;
    int detailed=0;
    int verbose=0;
    printf("\n");

    for(int banner=0;banner<argc; banner++)
    {
        if(strcmp(argv[banner],"-d")==0)
        {
            detailed=1;
        }
   
        if(strcmp(argv[banner],"-v")==0)
        {
            verbose=1;
        }
   
        if(strcmp(argv[banner],"-r")==0)
        {
            option=1;
            amount=atoi(argv[banner+1]);
        }
    }

    if(option==1)
    {
        roundRobin(amount, verbose, detailed);
    }
    
	else
    {
        firstComeFS(detailed,verbose);
    }
}

void roundRobin(int detailed,int verbose, int amount)
{
    int temporary;
    int process_number=0;
    int thread_switch=0;
    int process_switch=0;
    int number_of_processes=0;
    int number_of_threads=0;
    int thread_number=0;
    int arrival_time=0;
    int number_of_CPU=0;
    int cpu_time=0;
    int io_time=0;
    int array_IO_time[100];
    int total_time_IO=0;
    int IO_time_temporary=0;
    int CPU_time_temporary=0;
    int array_CPU_time[100];
    int CPU_time_full=0;
    int end_time=0;
    int final_temporary=0;
    int filler=0; 
    int time_tt=0;
    int count_t=0;
    int lost=0;
    double average_t=0;
    int cpuTimeQ[100];
    int ioTimeQ[100];
	
    fscanf(stdin, "%d %d %d", &process_number, &thread_switch, &process_switch);
    end_time=end_time+(process_switch*process_number);
    lost=process_number*process_switch;
    for(int i=0; i<process_number;i++)
    {
        fscanf(stdin, "%d %d", &number_of_processes, &number_of_threads);
        count_t=count_t+number_of_threads;
        end_time=end_time+(thread_switch*number_of_threads);
        lost=lost+(thread_switch*number_of_threads);
        for(int q=0; q<number_of_threads;q++)
        {
            fscanf(stdin, "%d %d %d", &thread_number, &arrival_time, &number_of_CPU);
            for(filler=0; filler<number_of_CPU-1; filler++)
            {
                fscanf(stdin, "%d %d %d",&temporary, &cpu_time,&io_time);
                //roundRobin changes here
                for(int r=0; r<number_of_CPU-1;r++)
                {
                    ioTimeQ[r]=io_time;
                    cpuTimeQ[r]=cpu_time;
                    if(ioTimeQ[r]-amount>=0)
                    {
						ioTimeQ[r]=ioTimeQ[r]-amount;
						cpuTimeQ[r]=cpuTimeQ[r]-amount;
					}
                    array_IO_time[filler]=ioTimeQ[r];
                    array_CPU_time[filler]=cpuTimeQ[r];  
                }
            }
            fscanf(stdin, "%d %d",&temporary, &cpu_time);
            array_CPU_time[filler]=cpu_time;
            //Detailed info reset
            IO_time_temporary=0;
            for(filler=0; filler<number_of_CPU-1;filler++)
            {
                total_time_IO=total_time_IO+array_IO_time[filler];
                IO_time_temporary=IO_time_temporary+array_IO_time[filler];
            }
            //Detailed info reset
            CPU_time_temporary=0;
            for(filler=0; filler<number_of_CPU;filler++)
            {
                CPU_time_full=CPU_time_full+array_CPU_time[filler];
                CPU_time_temporary=CPU_time_temporary+array_CPU_time[filler];
            }
                final_temporary=CPU_time_temporary+IO_time_temporary;
                time_tt=time_tt+final_temporary+thread_switch;
                if(thread_number==1)
                {
                    time_tt=time_tt+process_switch;
                }
                average_t=average_t+(time_tt-arrival_time);
                if(detailed==1)
                {
                    printf("\n\nThread %d of Process %d: \n\n",thread_number,number_of_processes);  
                    printf("Arrival time: %d \n",arrival_time); 
                    printf("Service time: %d units \n",final_temporary-IO_time_temporary); 
                    printf("I/O time: %d units \n",IO_time_temporary); 
                    printf("Turnaround time: %d units \n",time_tt-arrival_time) ;
                    printf("Finish time: %d units \n\n",time_tt);
                }
                if(verbose==1)
                {
                    if(thread_number==1 && number_of_processes==1)
                    {
                        printf("Not available, please try again later\n");
                    }
                }
        } 
    }
    end_time=end_time+CPU_time_full+total_time_IO;
    double average_turn=average_t/count_t;
    double one_CPU=(end_time-lost);
    one_CPU=(one_CPU/end_time);
    printf("\n\nTotal Time required is %d units\n",end_time);
    printf("Average Turnaround Time is %.2lf time units \n",average_turn);
	printf("CPU Utilization is %.2lf \n",one_CPU*100);
}

void firstComeFS(int detailed,int verbose)
{
//need to change all of these names
    int number_of_processes=0;
	int thread_switch=0;
    int process_switch=0;
    int process_number=0;	
    int number_of_threads=0;
    int thread_number=0;
    int arrival_time=0;
    int number_of_CPU=0;
    int cpu_time=0;
    int io_time=0;
    int array_IO_time[100];
    int total_time_IO=0;
    int CPU_time_temporary=0;
    int array_CPU_time[100];	
    int IO_time_temporary=0;
    int time_tt=0;
    int count_t=0;
    int lost=0;
	int temporary;
    int CPU_time_full=0;
	int filler=0;
    int end_time=0;
    int final_temporary=0;	
    double average_t=0;

    //Read first set of info
    fscanf(stdin, "%d %d %d", &process_number, &thread_switch, &process_switch);
    end_time=end_time+(process_switch*process_number);
    //Start overhead count
    lost=process_number*process_switch;
    //Start nested for loop
    for(int i=0; i<process_number;i++)
    {
        fscanf(stdin, "%d %d", &number_of_processes, &number_of_threads);
        count_t=count_t+number_of_threads;
        end_time=end_time+(thread_switch*number_of_threads);
        lost=lost+(thread_switch*number_of_threads);
        for(int q=0; q<number_of_threads;q++)
        {
            fscanf(stdin, "%d %d %d", &thread_number, &arrival_time, &number_of_CPU); 
            for(filler=0; filler<number_of_CPU-1;filler++)
            {
                //  fscanf(stdin, "%d %d %d",&temporary, &cpu_time,&io_time);
	            fscanf(stdin,"%d", &temporary);
	            fscanf(stdin,"%d", &cpu_time);
	            fscanf(stdin,"%d", &io_time);
                array_IO_time[filler]=io_time;
                array_CPU_time[filler]=cpu_time;      
            }
            fscanf(stdin, "%d %d",&temporary, &cpu_time);
            array_CPU_time[filler]=cpu_time;
            //Detailed info reset
            IO_time_temporary=0;
            for(filler=0; filler<number_of_CPU-1;filler++)
            {
                total_time_IO=total_time_IO+array_IO_time[filler];
                IO_time_temporary=IO_time_temporary+array_IO_time[filler];
            }
            //Detailed info reset
            CPU_time_temporary=0;
            for(filler=0; filler<number_of_CPU;filler++)
            {
                CPU_time_full=CPU_time_full+array_CPU_time[filler];
                CPU_time_temporary=CPU_time_temporary+array_CPU_time[filler];
            }
            final_temporary=CPU_time_temporary+IO_time_temporary;
            time_tt=time_tt+final_temporary+thread_switch;
            while(thread_number==1)
            {
                time_tt=time_tt+process_switch;
            }
            average_t=average_t+(time_tt-arrival_time);
            if(detailed==1)
            {
                printf("\n\n The threads %d of Process %d: \n\n",thread_number,number_of_processes);  
                printf("The arrival time is: %d \n",arrival_time); 
                printf("The service time is: %d units \n",final_temporary-IO_time_temporary); 
                printf("The I/O time is: %d units \n",IO_time_temporary); 
                printf("Turnaround time: %d units \n",time_tt-arrival_time) ;
                printf("Finish time: %d units \n\n",time_tt);
            }
            if(verbose==1)
            {
                if(thread_number==1 && number_of_processes==1)
                {
                    printf("Not available, please try again later\n");
                }
            }
        }
    }
    end_time=end_time+CPU_time_full+total_time_IO;
    double average_turn=average_t/count_t;
    double one_CPU=(end_time-lost);
    one_CPU=(one_CPU/end_time);
    printf("\n\n This program requires a total time of %d units\n",end_time);
    printf("This files average turnaround time is %.2lf time units \n",average_turn);
    printf("This file's CPU utillization is %.2lf \n",one_CPU*100);
}