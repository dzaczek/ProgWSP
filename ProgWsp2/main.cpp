#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <time.h>
#include <fstream>
#include <iterator>
#include <string>
#include <array>
#include <cmath>

#include <time.h> //usun ze sleepami
#include <unistd.h>

#include <sys/time.h>//for timestamp

using namespace std;


//#define NUM_THREADS     4

#define SIZE_ARRAY    256
/*
 -*
 -*
 -* g++ -std=c++17  zad2av2.cpp -pthread -g
 -
* -*
 -*
 -*/
    typedef unsigned long long timestamp_t;


static int ilosc_przedzialow=SIZE_ARRAY;
static int size_histogram=SIZE_ARRAY;
static int zakres_liczb=8192;
static long long int ilosc_losowan=10000000;
static int rozmiar_p=zakres_liczb/ilosc_losowan;
vector<int>  vectorint;
//std::array <int,SIZE_ARRAY> histogram;
int histogram[SIZE_ARRAY];

string filename_data="orginal.txt";
int NUM_THREADS=8192;

  static timestamp_t get_timestamp()
    {
      struct timeval now;
      gettimeofday (&now, NULL);
      return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
    }




struct thread_data{
   int  thread_id;
   int ilosc_w;

};

void *THE_FUNCTION(void *threadarg)
{
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;
   int PRZEDZIAL_rozmiar=ilosc_losowan/my_data->ilosc_w;
   int PRZEDZIAL_zakres_min=PRZEDZIAL_rozmiar*my_data->thread_id;
   int PRZEDZIAL_zakres_maks=PRZEDZIAL_zakres_min+PRZEDZIAL_rozmiar;
   int *wsk_array_hist;
   wsk_array_hist=histogram;
   for(long long int sek=PRZEDZIAL_zakres_min;sek<PRZEDZIAL_zakres_maks;++sek)
   {


    long long numerprzedzialu=(vectorint[sek] * ilosc_przedzialow-1)/zakres_liczb;
    //cout <<"\t\tID: " << my_data->thread_id<< " numerprzedzialu"  <<  numerprzedzialu<< endl;
    //cout <<"\t\tID: " << my_data->thread_id<< " sek"  <<  sek<< endl; 
    //wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
    if(numerprzedzialu<ilosc_przedzialow && numerprzedzialu>=0){
    wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
    
   // wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
    // cout << numerprzedzialu << " " << histogram[numerprzedzialu] << " "<< w0pk <<endl;
    }
    else
    {
      cout <<"numerprzedzialu ->"<< numerprzedzialu;

    }
   }
   //cout << "\t\tThread ID : " << my_data->thread_id<<endl ;
   //cout << "\t\t Message : " << my_data->ilosc_w << endl;

   //cout << "\t\t TID:"<<my_data->thread_id<<"\n\t\tPrzedzial Rozmiar" <<PRZEDZIAL_rozmiar<<"\n\t\tPrzedzial MIN: "<<PRZEDZIAL_zakres_min<<"\n\t\t Przedzial MAKS: "<<PRZEDZIAL_zakres_maks<<"\n"<<endl;
   //cout << "\t\tilosc_losowan->"<<ilosc_losowan<<endl;
   //cout << "\t\tilosc_przedzialow->"<<ilosc_przedzialow<<endl;
   //cout <<  "\t\t przyklad waetosci z zakresu" << histogram[PRZEDZIAL_zakres_min] <<endl ; 
  // pthread_exit(NULL);
}

//losujemy liczbe z zakresu
int random2()
{

    return  rand() % zakres_liczb + 1;
}
//load from file
void inputVint(string  filename)
{
    int invar;
    ifstream inputFile;
    inputFile.open(filename);
    //inputFile >> invar;
  //  cout << invar<<endl;
    //inputFile >> invar;
    //cout << invar<<endl;
    while(inputFile>>invar){
        vectorint.push_back(invar);
    }
    inputFile.close();
   // cout<<histogram[1]<<" "<<histogram[10]<<endl;
}

//safe to file
void outputVint(vector<int> bleblebla, string filename)
{
    ofstream outputFile;
    outputFile.open(filename);


    for (auto n : bleblebla)
        outputFile << n << '\t';

    outputFile.close();
}
bool check_if_file_exist(string filename)
{
  //return std::filesystem::exists(filename);
  //return std::experimental::filesystem::exists(filename);
  std::ifstream infile(filename);
   return infile.good();
}

void tworzHistogram()
{
  //tworzy zawsze poprawny histogram pojedynczy przebieg
 int rozmiar_p=zakres_liczb/ilosc_losowan;

 int w0pk;
 int b;

 for (auto w0pk : vectorint)
 {

    int numerprzedzialu=(w0pk * ilosc_przedzialow-1)/zakres_liczb;
    //numerprzedzialu=numerprzedzialu;
    //cout <<numerprzedzialu <<" ";
    if(numerprzedzialu<size_histogram && numerprzedzialu>=0){
      histogram[numerprzedzialu]=histogram[numerprzedzialu]+1;
    // cout << numerprzedzialu << " " << histogram[numerprzedzialu] << " "<< w0pk <<endl;
    }
    else
    {
      cout <<"numerprzedzialu ->"<< numerprzedzialu;
    }

}

 
}


int createSumArray(int* arr, int size)
{
 int wynik=0;
 for (int i = 0; i < size; i++)
    wynik += arr[i];

return wynik;
}

 double diffclock( clock_t clock2, clock_t clock1 ) {

        double diffticks = clock1 - clock2;
        double diffms    = diffticks / ( CLOCKS_PER_SEC / 1 );

        return diffms;
    }


void array_histogra_to_file(string filename)
{
  //int arr*=histogram;
  ofstream myfile(filename);
  if(myfile.is_open())
  {
    for(int i=0;i<size_histogram;++i){ myfile << histogram[i]<<"\n";}
  }
//  cout <<"Zapisano plik wynikowy historamu o nazwie: "<<filename<<endl;
}
//insert data to table
void data_generate()
{
for (long long int i=0; i<ilosc_losowan; i++)
{
    vectorint.push_back(random2());
}
cout <<"\t Wygenerowano tablice o rozmarze: "  <<ilosc_losowan<<endl;
}
int main ()
{
   //cout << "**** max_size: " << vectorint.max_size() << "\n";
   cout <<"*** PID: "<< getpid()<<endl;
   sleep (3);
   pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];
   srand(time(NULL));
   int rc;
   int i;

  //generujemy vector losowych danych z zakresu
  if(!check_if_file_exist(filename_data)){
   data_generate();
   outputVint(vectorint,filename_data);
   }
   else
   {
     inputVint(filename_data);
     cout <<"plik istnial zaladowano dane z pliku: "<< filename_data<<endl;
    // cout <<vectorint[1]<<vectorint[10]<<vectorint[15]<<endl;
   }

   //tworzymy histogram
  tworzHistogram();

 
  array_histogra_to_file("wzor.txt");

  //for (int i = 0; i < size_histogram; i++) {
  //      cout<< i<<"->"<<histogram[i]<<endl;
  //}
  //czyscimy tablice
  for (int i = 0; i < size_histogram; i++) {
        histogram[i] = '\0';

        
}
                                                        
cout<<"------------------------------------------------------------"<<endl;

cout<< "|THREADS|CORE TIME|Timestamp| Chrono |Ele  His| TIME/CORE |"<<endl;
cout<<"------------------------------------------------------------"<<endl;
while (NUM_THREADS>=1)
{
//  cout<<"\t\t\t ***START THR***"<<" \tNR: "<<NUM_THREADS <<endl;
     clock_t begin = clock();
     timestamp_t t0 = get_timestamp();
     auto start = std::chrono::steady_clock::now();
   for( i=0; i < NUM_THREADS; i++ ){
      //cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].ilosc_w = NUM_THREADS;

      rc = pthread_create(&threads[i],NULL,THE_FUNCTION,(void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);

      }
   // pthread_detach(threads[i]);      
   }
     for(i=0;i<NUM_THREADS;i++)pthread_join(threads[i], NULL);
  // cout <<"test" <<pthread_exit(NULL)<<endl;
  timestamp_t t1 = get_timestamp();
  clock_t end = clock();
  auto stop = std::chrono::steady_clock::now();

 //for(i=0; i<NUM_THREADS; i++)
  //  {
   //         status*   status;
    //        pthread_join(threads[i], &status);
    //}

      double elapsed_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop- start).count();
      string s = to_string(NUM_THREADS);
      double secs = (t1 - t0) / 1000000.0L;
      double diffcores=diffclock(begin,end);
      double diffcore=diffcores/NUM_THREADS;
    //cout<< "|"<<NUM_THREADS <<"|"<<diffclock(begin,end)<<"|"<< secs<<"|"<<elapsed_seconds<<"|"<< createSumArray(histogram,SIZE_ARRAY) <<"|"<<endl;
    printf("|%7d|%9f|%9f|%5f|%8d|%11f|\n",NUM_THREADS,diffcores,secs,elapsed_seconds/1000000000,createSumArray(histogram,SIZE_ARRAY),diffcore);
    cout<<"------------------------------------------------------------"<<endl;

//   cout<<"\t\t\t ***END THR***"<<endl;
   array_histogra_to_file(s+"watek.txt");
   
   const int pki=(NUM_THREADS<=2)?NUM_THREADS=NUM_THREADS-1:NUM_THREADS=NUM_THREADS/2;
   
    for (int i = 0; i < size_histogram; i++) {
        histogram[i] = '\0';  }

        
 }



    //for (int i = 0; i < size_histogram; i++) {
    //    cout<< i<<"->"<<histogram[i]<<endl;
  //}
   //cout<<"\t\t\t ***SAFE TO FILE***"<<endl;

   
   cout<<"\t\t\t ***END***"<<endl;
   return 0;
}


