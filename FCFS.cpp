#include<iostream>
#include<algorithm>
using namespace std;

struct User
{
    int id;
    int arrival_time;
    int burst_time;
};
bool compareUsers(User user1, User user2){
        return user1.arrival_time<user2.arrival_time;
    }
int main(){
    int n,i;
    cout<<"Enter the number of users: ";
    cin>>n;

    User user[n];

    for(i=0;i<n;i++){
        cout<<"Enter user ID: ";
        cin>>user[i].id;
        cout<<"Enter user Arrival time: ";
        cin>>user[i].arrival_time;
        cout<<"Enter user Burst time: ";
        cin>>user[i].burst_time;
        cout<<"*************************"<<endl;

    }

sort(user,user+n,compareUsers);
int waiting_time[n];
int turn_around_time[n];
int starting_time[n];
int completing_time[n];
waiting_time[0]=0;
starting_time[0]=0;
for ( i = 1; i < n; i++){
    starting_time[i]=starting_time[i-1]+user[i-1].burst_time; 
}
for ( i = 0; i < n; i++){
    completing_time[i]=starting_time[i]+user[i].burst_time; 
}
for ( i = 0; i < n; i++)
{
    turn_around_time[i]= completing_time[i]-user[i].arrival_time ;
}
for ( i = 0; i < n; i++){
    waiting_time[i]=turn_around_time[i]-user[i].burst_time; 
}
cout<<"ID no.\tArrivalTime\tBurstTime\tStartTime\tCompleteTime\tTurnaroundTime\tWaitingTime\n"<<endl;
int t_waitingtime=0, t_turn_around_time=0;
for ( i = 0; i < n; i++)
{
    t_waitingtime+=waiting_time[i];
    t_turn_around_time+=turn_around_time[i];
    cout<< user[i].id<<"\t\t"<<user[i].arrival_time<<"\t\t"<< user[i].burst_time<<"\t\t"<<starting_time[i]<<"\t\t"<<completing_time[i]<<"\t\t"<< turn_around_time[i]<<"\t\t"<< waiting_time[i]<< endl;
}

cout<<"Average time: "<<(float)t_waitingtime/(float)n<<endl;
float temp=(float)t_turn_around_time/n;
cout<<"Average Turnaround time: "<<temp<<endl;
cout<<"ThroughPut time: "<<(float)temp/n<<endl;
return 0;
}
