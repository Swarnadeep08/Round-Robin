#include <iostream>
#include <cstdio>
using namespace std;

struct PCB
{
    int pid, arrival, burst, rem_burst, turnaround, waiting;
}p[10], temp;

void pline(int x){
    for(int i=0; i<x; i++){
        cout<<"-";
    }
    cout<<"\n";
}

int main()
{
    int i, j, num, count, quantum, qt, ex=0, total_tat=0, total_wt=0;
    float avg_tat=0.0, avg_wt=0.0;

    cout<<"Enter process number: ";
    cin>>num;
    cout<<"Enter process sequence:\n";
    for(i=0; i<num; i++){
        p[i].pid = i+1;
        cout<<"Enter arrival time and burst time of process "<<p[i].pid<<": ";
        cin>>p[i].arrival>>p[i].burst;
        p[i].rem_burst = p[i].burst;
    }

    cout<<"Enter the time quantum: ";
    cin>>quantum;

    // sorting the process on their arrival time
    for(i=0; i<num-1; i++){
        for(j=0; j<num-i-1; j++){
            if(p[j].arrival > p[j+1].arrival)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    while(true){
        for(i=0, count=0; i<num; i++){
            qt = quantum;

            // check whether rem burst time is left or not
            if(p[i].rem_burst == 0){
                count++;
                continue;
            }

            // check whether rem burst time is greater than time quantum
            if(p[i].rem_burst > quantum){
                p[i].rem_burst = p[i].rem_burst - quantum;
            }
            else if(p[i].rem_burst >= 0)
            {
                qt = p[i].rem_burst;
                p[i].rem_burst = 0;
            }

            ex = ex + qt;
            p[i].turnaround = ex - p[i].arrival;

        }
        if(num==count){
            break;
        }

    }
    pline(44);
    cout<<"PID\tArrival\tBurst\tWait\tTurnaround\n";
    pline(44);
    for(i=0; i<num; i++){
        total_tat += p[i].turnaround;
        p[i].waiting = p[i].turnaround - p[i].burst;
        total_wt += p[i].waiting;
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }
    pline(44);
    avg_tat = (float) total_tat/num;
    avg_wt = (float) total_wt/num;

    printf("\nTotal Turnaround time: %d.", total_tat);
    printf("\nAverage Turnaround time: %.3f.", avg_tat);

    printf("\nTotal Waiting time: %d.", total_wt);
    printf("\nAverage Waiting time: %.3f.", avg_wt);

    return 0;
}
