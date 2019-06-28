#include <iostream>
#include <queue>
#include <ctime>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>
using namespace std;

/**
 * @{
 * const param def
 */
const int max_thread = 11;
const double slp_gap = 1e-2;
const int max_strlen = 101;
const char* filename = "input.in";
/** } */

struct semaphore {
    semaphore(int init = 0): count(init) {}
    queue<int> blocked;
    int count;
};

struct thread_data {
    int thread_order;
    int apply_clock;
    int serve_clock;
    char thread_name[max_strlen];
};


//< semaphore def
queue<int> ready_queue;
semaphore r_w_w(1);
semaphore readercount_mutex(1);
int readercount = 0;
time_t start_clock, mid_clock;

inline int get_clock() {
    mid_clock = time(NULL);
    return int(mid_clock - start_clock);
}

void semWait(semaphore& sem, int thr_order) {
    sem.count --;
    if (sem.count < 0) {
        sem.blocked.push(thr_order);
        while (ready_queue.front() != thr_order) 
            sleep(slp_gap);
        ready_queue.pop();
    }
}

void semSignal(semaphore& sem, int thr_order) {
    sem.count ++;
    if (sem.count <= 0) {
        ready_queue.push(sem.blocked.front());
        sem.blocked.pop();
    }
}

void* Reader(void* threadarg) {
    // get thread data
    thread_data* sig_data;
    sig_data = (thread_data*)threadarg;
    semWait(readercount_mutex, sig_data->thread_order);
    if (readercount == 0) 
        semWait(r_w_w, sig_data->thread_order);
    readercount ++;
    semSignal(readercount_mutex, sig_data->thread_order);
    // function start
    mid_clock = time(NULL);
    int start_time = get_clock();
    printf ("%s\t%d\t%d\t%d\t%d\t%d\n",
            sig_data->thread_name, sig_data->thread_order, 
            sig_data->apply_clock, sig_data->serve_clock,
            start_time, start_time + sig_data->serve_clock);
    sleep(sig_data->serve_clock);
    //< function end
    semWait(readercount_mutex, sig_data->thread_order);
    readercount --;
    if (readercount == 0) 
        semSignal(r_w_w, sig_data->thread_order);
    semSignal(readercount_mutex, sig_data->thread_order);
    pthread_exit(NULL);
}

void* Writer(void* threadarg) {
    // get thread data
    thread_data* sig_data;
    sig_data = (thread_data*)threadarg;
    semWait(r_w_w, sig_data->thread_order);
    //< function start
    mid_clock = time(NULL);
    int start_time = get_clock();
    printf ("%s\t%d\t%d\t%d\t%d\t%d\n",
            sig_data->thread_name, sig_data->thread_order, 
            sig_data->apply_clock, sig_data->serve_clock,
            start_time, start_time + sig_data->serve_clock);
    sleep(sig_data->serve_clock);
    //< function end
    semSignal(r_w_w, sig_data->thread_order);
    pthread_exit(NULL);
}

int main() {
    freopen(filename, "r", stdin);
    int thread_num = 0;
    scanf("%d", &thread_num);
    pthread_t threads[max_thread];
    thread_data th_data[max_thread];
    for (int inc = 0; inc < thread_num; inc ++) {
        printf("main(): create thread, order %d\n", inc);
        th_data[inc].thread_order = inc;
        scanf("%s %d %d", th_data[inc].thread_name, 
              &th_data[inc].apply_clock, &th_data[inc].serve_clock);
        ready_queue.push(inc);
    }
    start_clock = time(NULL);
    int have_wait = 0;
    printf("name\torder\tapply\tserve\tstart\tfinish\n");
    while (!ready_queue.empty()) {
        int inc = ready_queue.front(); ready_queue.pop();
        sleep(th_data[inc].apply_clock - have_wait);
        have_wait = th_data[inc].apply_clock;
        assert(!pthread_create(&threads[inc], NULL, 
               th_data[inc].thread_name[0] == 'r' ? Reader : Writer, (void*)&(th_data[inc])));
    }
    pthread_exit(NULL);
    return 0;
}
