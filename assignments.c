// Q.B1  . Write a program using open ( ), read ( ) and write ( ) system calls for copying number of byte from one file to another file. The program must be interactive and must take input from the user 
// as <name of existing file>, <name of new file> and <number of byte to be copied>.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{

    int n;
    printf("Enter the number of bytes to be read: ");
    scanf("%d", &n);
    char file1[1000],file2[1000];

    printf("Enter the name of the file to be read: ");
    scanf("%s", file1);
    printf("Enter the name of the file to be written: ");
    scanf("%s", file2);
    int fd = open(file1, O_RDONLY);
    if(fd == -1)
    {
        printf("File not found");
        return 0;
    }
    char buf[n];
    int ret = read(fd, buf, n);

    int wr = open(file2, O_WRONLY);
   
    int wrt = write(wr, buf, n);
    printf("number of copied bytes %d\n", wrt);
    return 0;
}

=============================================================================================



// Q.B1 Write a program to take integer from user as input and generate same number of child process with fork ( ) system call, also print their PID along with parent PID.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int n;
    printf("Enter the integer number : ");
    scanf("%d",&n);
	for(int i=0;i<n;i++) 
	{
		if(fork() == 0)
		{
			printf("Here is the [SON] pid %d from the [parent] pid  
                                        %d\n",getpid(),getppid());
			exit(0);
		}
	            else{
                                     wait(NULL);
                         }
	}
	return 0;
}

================================================================================================================

Q.B2 Write a program to demonstrate that a parent process is waiting for child process to end.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    if(fork()==0)
    {
        int a=execl("parent","parent",NULL);
        exit(0);
    }

    wait(NULL);
    printf("\nParent has done waiting for the child");

    return 0;
}
OUTPUT:

==============================================================================================================

Q.1 Write a generic code in C of CPU Scheduling Algorithms, first come first served (FCFS) and Shortest Job First (SJF). In the program first user will input data in sequence like, Process no. ,arrival time, and Burst Time and then select any one of the algorithm to get turnaround time (TAT), Waiting Time (WT) and Response Time(RT) for each process and their averages.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void swap(int *x, int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void sortat(int p[], int at[], int bt[], int n)
{
  int i, j;
  for(i=0;i<n;i++)
  {
      for(j=i+1;j<n;j++)
      {   
	  if(at[i]>at[j])
	  { 
	        swap(&p[i], &p[j]);
		swap(&at[i], &at[j]);
		swap(&bt[i], &bt[j]);
	   }
	   else if(at[i]==at[j])
	   {
	      if(bt[i]>bt[j])
                 swap(&p[i], &p[j]);
                 swap(&at[i], &at[j]);
                 swap(&bt[i], &bt[j]);
	   }
       }
  }
}
void tatwt( int ct[], int at[], int bt[], int tat[], int wt[], int n)
{
   int i;
   for(i=0;i<n;i++)
   {
	tat[i]=ct[i]-at[i];
	wt[i]=tat[i]-bt[i];
   }
}

void fcfs(){
	int bt[10]={0},at[10]={0},tat[10]={0},wt[10]={0},ct[10]={0};
	int n,sum=0;
	float totalTAT=0,totalWT=0;
	printf("Enter number of processes	");
	scanf("%d",&n);
	printf("Enter arrival time and burst time for each process\n\n");

	for(int i=0;i<n;i++)
	{
		printf("Arrival time of process[%d]	",i+1);
		scanf("%d",&at[i]);
		printf("Burst time of process[%d]	",i+1);
		scanf("%d",&bt[i]);
		printf("\n");
	}
	for(int j=0;j<n;j++)
	{
		sum+=bt[j];
		ct[j]+=sum;
	} 
	for(int k=0;k<n;k++)
	{
		tat[k]=ct[k]-at[k];
		totalTAT+=tat[k];
	}
	for(int k=0;k<n;k++)
	{
		wt[k]=tat[k]-bt[k];
		totalWT+=wt[k];
	}
	printf("Solution: \n\n");
	printf("P#\t AT\t BT\t CT\t TAT\t WT\t\n\n");
	for(int i=0;i<n;i++)
	{
		printf("P%d\t %d\t %d\t %d\t %d\t %d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
	}	
	printf("\n\nAverage Turnaround Time = %f\n",totalTAT/n);
	printf("Average WT = %f\n\n",totalWT/n);
}
void sjf()
{
   int *p, *at, *bt, *tat, *wt, *ct, pos, i, j, min=1000, n;
  float awt=0, atat=0;
  printf("\nenter the number of process:");
  scanf("%d", &n);
  p=(int*)malloc(n*sizeof(int));
  at=(int*)malloc(n*sizeof(int));
  bt=(int*)malloc(n*sizeof(int));
  ct=(int*)malloc(n*sizeof(int));
  wt=(int*)malloc(n*sizeof(int));
  tat=(int*)malloc(n*sizeof(int));
  printf("enter the process");
  for(i=0;i<n;i++)
  {
	scanf("%d",&p[i]);
  }
  printf("enter the arrival time");
  for(i=0;i<n;i++)
  {
	scanf("%d",&at[i]);
  }
  printf("enter the burst time");
  for(i=0;i<n;i++)
  {
	scanf("%d",&bt[i]);
  }
  sortat(p, at, bt, n);
  ct[0]=at[0] + bt[0];
  for(i=1; i<n; i++)
  {
	for(j=i; j<n; j++)
	{
	    if(at[j]<=ct[i-1])
	   {
              if(bt[j]<min)
              {
                 min=bt[j];
                 pos=j;
              }
	   }
	}
    swap(&p[i], &p[pos]);
    swap(&at[i], &at[pos]);
    swap(&bt[i], &bt[pos]);
    min=1000;
    ct[i]=ct[i-1]+bt[i];
  }
  tatwt(ct, at, bt, tat, wt, n);
  printf("\nP#\t AT\t BT\t CT\t TAT\t WT"); 
  for(i=0;i<n;i++)
  {
    printf("\n%d\t %d\t %d\t %d\t %d\t %d",p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
  }
  for(i=0;i<n;i++)
  { 
    atat+=tat[i];
    awt+=wt[i];
  }
  atat=atat/n;
  awt=awt/n;
  printf("\n avg tat=%.2f and avg wt=%.2f",atat, awt); 
}
int main(){
    int number;
    printf("Enter 1 for FCFS and 2 for SJF: ");
    scanf("%d", &number);
    if (number == 1)
    {
        fcfs();
    }
    else if (number == 2)
    {
        sjf();
    }
    else
    {
        printf("Invalid input");
    }
    return 0;
}

===========================================================================================================


Q.2  Write another code that will randomly generate burst time for processes by fixing lower and upper limit of burst time. Apply FCFS and SJF algorithm, after that write your observation on the basis of TAT, WT and RT.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void swap(int *x, int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
void sortat(int p[], int at[], int bt[], int n)
{
  int i, j;
  for(i=0;i<n;i++)
  {
      for(j=i+1;j<n;j++)
      {   
	  if(at[i]>at[j])
	  { 
	        swap(&p[i], &p[j]);
		swap(&at[i], &at[j]);
		swap(&bt[i], &bt[j]);
	   }
	   else if(at[i]==at[j])
	   {
	      if(bt[i]>bt[j])
                 swap(&p[i], &p[j]);
                 swap(&at[i], &at[j]);
                 swap(&bt[i], &bt[j]);
	   }
       }
  }
}
void tatwt( int ct[], int at[], int bt[], int tat[], int wt[], int n)
{
   int i;
   for(i=0;i<n;i++)
   {
	tat[i]=ct[i]-at[i];
	wt[i]=tat[i]-bt[i];
   }
}
void fcfs(){
	int bt[10]={0},at[10]={0},tat[10]={0},wt[10]={0},ct[10]={0};
	int n,sum=0;
	float totalTAT=0,totalWT=0;
	printf("Enter number of processes	");
	scanf("%d",&n);
	printf("Enter arrival time and burst time for each process\n\n");
	for(int i=0;i<n;i++)
	{
		printf("Arrival time of process[%d] ",i+1);
		scanf("%d",&at[i]);
                             bt[i] = rand() % 11 + 1;
                             printf("Burst time of process[%d] %d",i+1,bt[i]);
                             printf("\n");
	}
	for(int j=0;j<n;j++)
	{
		sum+=bt[j];
		ct[j]+=sum;
	} 
	for(int k=0;k<n;k++)
	{
		tat[k]=ct[k]-at[k];
		totalTAT+=tat[k];
	}
	for(int k=0;k<n;k++)
	{
		wt[k]=tat[k]-bt[k];
		totalWT+=wt[k];
	}
	printf("Solution: \n\n");
	printf("P#\t AT\t BT\t CT\t TAT\t WT\t\n\n");
	for(int i=0;i<n;i++)
	{
		printf("P%d\t %d\t %d\t %d\t %d\t %d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
	}
	printf("\n\nAverage Turnaround Time = %f\n",totalTAT/n);
	printf("Average WT = %f\n\n",totalWT/n);
}
void sjf()
{
   int *p, *at, *bt, *tat, *wt, *ct, pos, i, j, min=1000, n;
  float awt=0, atat=0;
  printf("\n  enter the number of process:");
  scanf("%d", &n);
  p=(int*)malloc(n*sizeof(int));
  at=(int*)malloc(n*sizeof(int));
  bt=(int*)malloc(n*sizeof(int));
  ct=(int*)malloc(n*sizeof(int));
  wt=(int*)malloc(n*sizeof(int));
  tat=(int*)malloc(n*sizeof(int));
  printf("enter the process");
  for(i=0;i<n;i++)
  {
	scanf("%d",&p[i]);
  }
  printf("enter the arrival time");
  for(i=0;i<n;i++)
  {
	scanf("%d",&at[i]);
  }
  for(i=0;i<n;i++)
  {
                             bt[i] = rand() % 11 + 1;
                             printf("Burst time of process[%d] %d",i+1,bt[i]);
	           printf("\n");
  }
  sortat(p, at, bt, n);
  ct[0]=at[0] + bt[0];
  for(i=1; i<n; i++)
  {
	for(j=i; j<n; j++)
	{
	    if(at[j]<=ct[i-1])
	   {
              if(bt[j]<min)
              {
                 min=bt[j];
                 pos=j;
              }
	   }
	}
    swap(&p[i], &p[pos]);
    swap(&at[i], &at[pos]);
    swap(&bt[i], &bt[pos]);
    min=1000;
    ct[i]=ct[i-1]+bt[i];
  }
  tatwt(ct, at, bt, tat, wt, n);
  printf("\nP#\t AT\t BT\t CT\t TAT\t WT"); 
  for(i=0;i<n;i++)
  {
    printf("\n%d\t %d\t %d\t %d\t %d\t %d",p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
  }
  for(i=0;i<n;i++)
  { 
    atat+=tat[i];
    awt+=wt[i];
  }
  atat=atat/n;
  awt=awt/n;
  printf("\n avg tat=%.2f and avg wt=%.2f",atat, awt); 
}
int main(){
    int number;
    printf("Enter 1 for FCFS and 2 for SJF: ");
    scanf("%d", &number);
    if (number == 1)
    {
        fcfs();
    }
    else if (number == 2)
    {
        sjf();
    }
    else
    {
        printf("Invalid input");
    }
    return 0;
}

=========================================================================================================

Q1. Write generic code in C of CPU Scheduling Algorithms, Shortest Remaining Time First (SRTF) and Premptive Priority. In the program first user will input data in sequence like, process no., arrival time, and burst time. Also take priority as input in case of Preemptive Priority algorithm. Calculate turnaround time (TAT), waiting time (WT) and response time (RT) for each process and their averages.
#include <stdio.h>
#include<stdio.h>
struct process
{
    int WT,AT,BT,TAT,PT;
};
struct process a[10];
void priority()
{
    int n,temp[10],t,count=0,short_p;
    float total_WT=0,total_TAT=0,Avg_WT,Avg_TAT;
    printf("Enter the number of the process\n");
    scanf("%d",&n);
    printf("Enter the arrival time , burst time and priority of the process\n");
    printf("ArrivalTime BurstTime PriorityTime\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",&a[i].AT,&a[i].BT,&a[i].PT);
        temp[i]=a[i].BT;
    }
    a[9].PT=10000;
    
    for(t=0;count!=n;t++)
    {
        short_p=9;
        for(int i=0;i<n;i++)
        {
            if(a[short_p].PT>a[i].PT && a[i].AT<=t && a[i].BT>0)
            {
                short_p=i;
            }
        }
        a[short_p].BT=a[short_p].BT-1;
        if(a[short_p].BT==0)
        {
             count++;
            a[short_p].WT=t+1-a[short_p].AT-temp[short_p];
            a[short_p].TAT=t+1-a[short_p].AT;
            
            total_WT=total_WT+a[short_p].WT;
            total_TAT=total_TAT+a[short_p].TAT;       
        }
    }
    
    Avg_WT=total_WT/n;
    Avg_TAT=total_TAT/n;
   
    printf("PID WaitingTime TurnAroundTime\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t %d\t%d\n",i+1,a[i].WT,a[i].TAT);
    }
    printf("Avg waiting time of the process  is %f\n",Avg_WT);
    printf("Avg turn around time of the process is %f\n",Avg_TAT);    
}

void srtf()
{
    int at[10], bt[10], rt[10], endTime, i, smallest;
    int remain = 0, n, time, sum_wait = 0, sum_turnaround = 0;
    printf("Enter no of Processes : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter arrival time for Process P%d : ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter burst time for Process P%d : ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }
    printf("\n\nProcess\t|  Arrival Time  |  Burst Time  |  Turnaround Time  |  Waiting Time  \n\n");
    rt[9] = 9999;
    for (time = 0; remain != n; time++)
    {
        smallest = 9;
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0)
            {
                smallest = i;
            }
        }
        rt[smallest]--;
        if (rt[smallest] == 0)
        {
            remain++;
            endTime = time + 1;
            printf("\nP[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d", smallest + 1, at[smallest], bt[smallest], endTime - at[smallest], endTime - bt[smallest] - at[smallest]);
            sum_wait += endTime - bt[smallest] - at[smallest];

            sum_turnaround += endTime - at[smallest];
        }
    }

    printf("\n\nAverage waiting time = %f\n", sum_wait * 1.0 / n);

    printf("Average Turnaround time = %f", sum_turnaround * 1.0 / 5);

}

int main()
{
    int choice;
    printf("Enter the choice\n");
    printf("1. Priority\n");
    printf("2. SRTF\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            priority();
            break;
        case 2:
            srtf();
            break;
        default:
            printf("Invalid choice\n");
    }
    return 0;
}

=================================================================================================================

Q2. Write another code that will randomly generate burst time, priority and arrival time for processes by fixing lower and upper limit of all inputs. Apply SRTF and Preemptive priority algorithm, after that write your observation on the basis of TAT, WT and RT.
#include <stdio.h>
#include <stdlib.h>
int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}
typedef struct process_stats
{
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int priority;
    int turnaround_time;
    int completion_time;
    int remaining_time;
    int response_time;
} process;
process arrived[100];
int k = 0;
void merge(process *arr, int l, int mid, int r)
{
    int i, j, k;
    int n1 = mid - l + 1;
    int n2 = r - mid;
    process left[n1], right[n2];
    for (i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (left[i].arrival_time <= right[j].arrival_time)
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}
void mergeSort(process *arr, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    merge(arr, l, mid, r);
}
int comparePriority(process p1, process p2)
{
    if (p1.priority < p2.priority)
        return 1;
    else if (p1.priority > p2.priority)
        return 0;
    else
    {
        if (p1.arrival_time < p2.arrival_time)
            return 1;
        else
            return 0;
    }
}
int compareRemainingTime(process p1, process p2)
{
    if (p1.remaining_time < p2.remaining_time)
        return 1;
    else if (p1.remaining_time > p2.remaining_time)
        return 0;
    else
    {
        if (p1.arrival_time < p2.arrival_time)
            return 1;
        else
            return 0;
    }
}
void push(process p, int (*comp)(process, process))
{
    arrived[k] = p;
    k++;
    int i = k - 1;
    while (i > 0 && comp(arrived[i], arrived[(i - 1) / 2]))
    {
        process temp = arrived[i];
        arrived[i] = arrived[(i - 1) / 2];
        arrived[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}
void pop(int (*comp)(process, process))
{
    arrived[0] = arrived[--k];
    int i = 0;
    int j = 2 * i + 1;
    if (j + 1 <= k && comp(arrived[j + 1], arrived[j]))
        j++;
    while (j <= k && comp(arrived[j], arrived[i]))
    {
        process temp = arrived[i];
        arrived[i] = arrived[j];
        arrived[j] = temp;
        i = j;
        j = 2 * i + 1;
        if (j + 1 <= k && comp(arrived[j + 1], arrived[j]))
            j++;
    }
}
int main()
{
    int mode;
    printf("Choose the scheduling algorithm: \n1. SRTF \n2. Priority\nYour Choice: ");
    scanf("%d", &mode);
    int (*comp)(process, process);
    if (mode == 1)
    {
        comp = compareRemainingTime;
    }
    else
    {
        comp = comparePriority;
    }
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[n], ans[n];
    for (int i = 0; i < n; i++)
    {
        p[i].arrival_time = get_rand(0, 100);
        p[i].burst_time = get_rand(1, 100);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        p[i].response_time = -1;
        if (mode == 2)
        {
            p[i].priority = get_rand(1, 100);
        }else{
            p[i].priority = 1;
        }
    }
    mergeSort(p, 0, n - 1);
    int time = 0;
    int avg_waiting = 0, avg_turnaround = 0, avg_response = 0;
    int cnt = 0, i = 0;
    while (cnt < n)
    {
        while (i < n && p[i].arrival_time <= time)
        {
            push(p[i], comp);
            i++;
        }
        if (k == 0)
        {
            time = p[i].arrival_time;
            continue;
        }
        process temp = arrived[0];
        pop(comp);
        temp.remaining_time--;
        time++;
        if (temp.response_time == -1)
            temp.response_time = time - temp.arrival_time - 1;
        if (temp.remaining_time == 0)
        {
            temp.completion_time = time;
            temp.turnaround_time = temp.completion_time - temp.arrival_time;
            temp.waiting_time = temp.turnaround_time - temp.burst_time;
            ans[temp.pid - 1] = temp;
            cnt++;
            avg_waiting += temp.waiting_time;
            avg_turnaround += temp.turnaround_time;
            avg_response += temp.response_time;
        }
        else
            push(temp, comp);
    }
    printf("\n\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time Waiting Time\tTurnaround Time\tResponse Time \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", ans[i].pid, ans[i].arrival_time, ans[i].burst_time, ans[i].priority, ans[i].completion_time, ans[i].waiting_time, ans[i].turnaround_time, ans[i].response_time);
    }
    printf("\nAverage Waiting Time: %f\n", (float)avg_waiting / n);
    printf("Average Turnaround Time: %f\n", (float)avg_turnaround / n);
    printf("Average Response Time: %f\n", (float)avg_response / n);
    return 0;
}

=========================================================================================================================

Q.1 . Write C program for Round Robin (RR) CPU Scheduling Algorithm. In the  program, first user will input data in sequence like, process no. and burst time. Also take Time Quantum as input. Calculate turnaround time (TAT), waiting  time (WT) and response time (RT) for each process and their averages.
#include<stdio.h>
int main()
{
      int i, n, total = 0, x, counter = 0, time_quantum;
      int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
      float average_wait_time, average_turnaround_time;
   printf("***********************************************************************\n");
      printf("------------I am Jay Mehra------------\n");
   printf("***********************************************************************\n");
      printf("Enter Total Number of Processes:\t");
      scanf("%d", &n);
      x = n;
      for(i = 0; i < n; i++)
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &arrival_time[i]);
            printf("Burst Time:\t");
            scanf("%d", &burst_time[i]);
            temp[i] = burst_time[i];
      }
      printf("\nEnter Time Quantum:\t");
      scanf("%d", &time_quantum);
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      for(total = 0, i = 0; x != 0;)
      {
            if(temp[i] <= time_quantum && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - time_quantum;
                  total = total + time_quantum;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
                  wait_time += total - arrival_time[i] - burst_time[i];
                  turnaround_time +=  total - arrival_time[i];
                  counter = 0;
            }
            if(i == n - 1)
            { i = 0;}
            else if(arrival_time[i + 1] <= total)
            {i++;}
            else
            { i=0;}
      }
      average_wait_time = wait_time * 1.0 / n;
      average_turnaround_time = turnaround_time * 1.0 / n;
      printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
      printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
      return 0;
}

=======================================================================================================================

Q.1  Write a C program to simulate multilevel feedback queue. Create 3 queue
with RR2 in first queue, with RR4, in second queue and FCFS in third queue. 
Create one CPU clock according to which CPU time is given to each queue. 
CPU time is divided among three queues, 8 time quantum for first queue, 16 
time quantum for second queue and 32 time quantum for third queue. 
(Implement this simulation by using concept of link list of structure, having 
several fields like PID, Burst time, Remaining Burst time, etc.) Consider below data to check your code:
Process No.  Burst time 
P1                   4
P2                   2
P3                   6
P4                   15
You may consider all processes are in first queue in the beginning of simulation. Also print value of TAT, RT and WT for each process and their average values of entire system.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Process
{
  int PID;
  int arr, bur, rem, rt, tat, wt;
  struct Process *next;
} typedef Process;

Process *head1 = NULL, *tail1;
Process *head2 = NULL, *tail2;
Process *head3 = NULL, *tail3;
Process *head4 = NULL, *tail4;

Process *create(int PID, int bur);
void enqueue(Process **head, Process **tail, Process *proc);
Process *dequeue(Process **head);

void MLF(int n, int q1, int q2, int q3, int rr1, int rr2);
void print(Process *head);

int main()
{
  printf("********************************************\n");
  printf("***************I am Jay Mehra***************\n");
  printf("********************************************\n");
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  printf("Enter the data of each process, space-separated:\n");
  printf("PID Burst_time\n");
  int pid, arr, bur;

  for (int i = 0; i < n; i++)
  {
    scanf("%d %d", &pid, &bur);
    enqueue(&head1, &tail1, create(pid, bur));
  }

  int q1quanta = 8, q2quanta = 16, q3quanta = 32;
  int rr1quanta = 2, rr2quanta = 4;

  MLF(n, q1quanta, q2quanta, q3quanta, rr1quanta, rr2quanta);
  print(head4);
}

Process *create(int PID, int bur)
{
  Process *proc = (Process *)malloc(sizeof(Process));
  proc->PID = PID;
  proc->arr = 0;
  proc->bur = proc->rem = bur;
  return proc;
}

void enqueue(Process **head, Process **tail, Process *proc)
{
  if (*head)
  {
    (*tail)->next = proc;
    *tail = (*tail)->next;
  }
  else
  {
    *head = proc;
    *tail = *head;
  }
  (*tail)->next = NULL;
}
Process *dequeue(Process **head)
{
  if (*head == NULL)
    return NULL;
  Process *p = *head;
  *head = (*head)->next;
  return p;
}

void MLF(int n, int q1, int q2, int q3, int rr1, int rr2)
{
  int time = 0, count = 0, t = 0;
  Process *p;
  while (count - n)
  {
    t = 0;
    while (t < q1 && head1)
    {
      p = dequeue(&head1);
      if (p->rem == p->bur)
        p->rt = time + t - p->arr;
      if (p->rem <= rr1)
      {
        t += p->rem;
        p->rem = 0;
        p->tat = time + t - p->arr;
        p->wt = p->tat - p->bur;
        enqueue(&head4, &tail4, p);
        count++;
      }
      else
      {
        p->rem -= t + rr1 <= q1 ? rr1 : q1 - t;
        t = t + rr1 <= q1 ? t + rr1 : q1;
        enqueue(&head2, &tail2, p);
      }
    }
    while (head1)
    {
      enqueue(&head2, &tail2, dequeue(&head1));
    }
    time += t;
    t = 0;
    while (t < q2 && head2)
    {
      p = dequeue(&head2);
      if (p->rem == p->bur)
        p->rt = time + t - p->arr;
      if (p->rem <= rr2)
      {
        t += p->rem;
        p->rem = 0;
        p->tat = time + t - p->arr;
        p->wt = p->tat - p->bur;
        enqueue(&head4, &tail4, p);
        count++;
      }
      else
      {
        p->rem -= t + rr2 <= q2 ? rr2 : q2 - t;
        t = t + rr2 <= q2 ? t + rr2 : q2;
        enqueue(&head3, &tail3, p);
      }
    }
    while (head2)
    {
      enqueue(&head3, &tail3, dequeue(&head2));
    }
    time += t;
    // fcfs
    t = 0;
    while (t < q3 && head3)
    {
      p = dequeue(&head3);
      if (p->rem == p->bur)
        p->rt = time + t - p->arr;
      if (p->rem + t <= q3)
      {
        // Process finished
        t += p->rem;
        p->rem = 0;
        p->tat = time + t - p->arr;
        p->wt = p->tat - p->bur;
        enqueue(&head4, &tail4, p);
        count++;
      }
      else
      {
        p->rem -= q3 - t;
        t = q3;
        enqueue(&head1, &tail1, p);
      }
    }
    while (head3)
    {
      enqueue(&head1, &tail1, dequeue(&head3));
    }
    time += t;
  }
}

void print(Process *head)
{
  
  printf("\n");
  printf("+---------------+---------------+---------------+---------------+\n");
  printf("|    Process    |  Turnaround   |    Waiting    |   Response    |\n");
  printf("|      ID       |     time      |     time      |     time      |\n");
  printf("+---------------+---------------+---------------+---------------+\n");
  float sumtat = 0, sumwt = 0, sumrt = 0, n = 0;
  while (head)
  {
    printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n", head->PID, head->tat, head->wt,
           head->rt);
    sumtat += head->tat;
    sumwt += head->wt;
    sumrt += head->rt;
    head = head->next;
    n++;
  }
  printf("+---------------+---------------+---------------+---------------+\n");
  printf("|    Average    |\t%.2f\t|\t%.2f\t|\t%.2f\t|\n", sumtat / n,
         sumwt / n, sumrt / n);
  printf("+---------------+---------------+---------------+---------------+\n");
}
==========================================================================================================================

Q.2  Write generic simulation code in C for RR algorithm for data given by user and perform the analysis of different time quantum values and find out the optimal value of time quantum for the parameter like, TAT, WT, and RT.


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef struct process
{
      int pid;
      int arrival_time;
      int burst_time;
      int waiting_time;
      int turnaround_time;
      int completion_time;
      int remaining_time;
} process;
process *p;
process running[1000], queue[1000];
int end = -1;
int front = -1;
void push(process p)
{
      if (front == -1)
      {
            front = 0;
      }
      end++;
      queue[end] = p;
}
void pop()
{
      front++;
}
process front_p()
{
      return queue[front];
}
void merge(process *arr, int l, int mid, int r)
{
      int i, j, k;
      int n1 = mid - l + 1;
      int n2 = r - mid;
      process left[n1], right[n2];
      for (i = 0; i < n1; i++)
            left[i] = arr[l + i];
      for (j = 0; j < n2; j++)
            right[j] = arr[mid + 1 + j];
      i = 0;
      j = 0;
      k = l;
      while (i < n1 && j < n2)
      {
            if (left[i].arrival_time <= right[j].arrival_time)
            {
                  arr[k] = left[i];
                  i++;
            }
            else
            {
                  arr[k] = right[j];
                  j++;
            }
            k++;
      }
      while (i < n1)
      {
            arr[k] = left[i];
            i++;
            k++;
      }
      while (j < n2)
      {
            arr[k] = right[j];
            j++;
            k++;
      }
}
void mergeSort(process *arr, int l, int r)
{
      if (l >= r)
            return;
      int mid = (l + r) / 2;
      mergeSort(arr, l, mid);
      mergeSort(arr, mid + 1, r);
      merge(arr, l, mid, r);
}
process current;
int push_signal = 0;
float roundRobinCPUScheduling(int n, int time_quantum)
{
      int waiting_time = 0, turnaround_time = 0;
      int time = 0;
      int cnt = 0;
      int i = 0;
      while (cnt < n)
      {
            while (i < n && p[i].arrival_time <= time)
            {
                  push(p[i]);
                  i++;
            }
            if (front == -1 || front > end)
            {
                  time = p[i].arrival_time;
                  continue;
            }
            if (push_signal == 1)
            {
                  push(current);
                  push_signal = 0;
            }
            current = front_p();
            pop();
            if (current.remaining_time <= time_quantum)
            {
                  time += current.remaining_time;
                  current.remaining_time = 0;
                  current.turnaround_time = time - current.arrival_time;
                  current.waiting_time = current.turnaround_time - current.burst_time;
                  current.completion_time = time;
                  running[cnt] = current;
                  cnt++;
                  waiting_time += current.waiting_time;
                  turnaround_time += current.turnaround_time;
            }
            else
            {
                  time += time_quantum;
                  current.remaining_time -= time_quantum;
                  push_signal = 1;
            }
      }
      return (float)waiting_time / n;
}
int main()
{
      int n;
      int r = 0;
      printf("***********************************************************************\n");
      printf("------------I am Jay Mehra------------\n");
      printf("***********************************************************************\n");
      printf("Enter the number of processes: ");
      scanf("%d", &n);
      p = (process *)malloc(n * sizeof(process));
      for (int i = 0; i < n; i++)
      {
            printf("\nEnter details for Process %d\n", i + 1);
            printf("Arrival Time: ");
            scanf("%d", &p[i].arrival_time);
            printf("Burst Time: ");
            scanf("%d", &p[i].burst_time);
            p[i].pid = i + 1;
            p[i].remaining_time = p[i].burst_time;
            r += p[i].burst_time;
      }
      mergeSort(p, 0, n - 1);
      float min_avg_waiting_time = 1000000000;
      int min_time_quantum = 0;
      for (int time_quantum = 1; time_quantum <= r; time_quantum++)
      {
            end = -1;
            front = -1;
            push_signal = 0;
            float avg_waiting_time = roundRobinCPUScheduling(n, time_quantum);
            if (avg_waiting_time < min_avg_waiting_time)
            {
                  min_avg_waiting_time = avg_waiting_time;
                  min_time_quantum = time_quantum;
            }
      }
      printf("\nTime quantum = %d", min_time_quantum);
      printf(" Average Waiting Time = %f\n", min_avg_waiting_time);
      return 0;
}
