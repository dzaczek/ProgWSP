#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <iterator>
#include <string>
#include <array>
#include <cmath>
using namespace std;

#define NUM_THREADS     10
#define SIZE_ARRAY    256
static int ilosc_przedzialow=SIZE_ARRAY;
static int size_histogram=SIZE_ARRAY;
static int zakres_liczb=4096;
static int ilosc_losowan=5000000;
static int rozmiar_p=zakres_liczb/ilosc_losowan;
vector<int>  vectorint;
//std::array <int,SIZE_ARRAY> histogram;
int histogram[SIZE_ARRAY];
string filename_data="orginal.txt";

//int hist;ogram[ilosc_przedzialow];


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
   for(int sek=PRZEDZIAL_zakres_min;sek<PRZEDZIAL_zakres_maks;++sek)
   {


    int numerprzedzialu=(vectorint[sek] * ilosc_przedzialow-1)/zakres_liczb;
    //cout <<"\t\tID: " << my_data->thread_id<< " numerprzedzialu"  <<  numerprzedzialu<< endl;
    //cout <<"\t\tID: " << my_data->thread_id<< " sek"  <<  sek<< endl; 
    wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
    if(numerprzedzialu<ilosc_przedzialow && numerprzedzialu>=0){
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

   cout << "\t\t TID:"<<my_data->thread_id<<"\n\t\tPrzedzial Rozmiar" <<PRZEDZIAL_rozmiar<<"\n\t\tPrzedzial MIN: "<<PRZEDZIAL_zakres_min<<"\n\t\t Przedzial MAKS: "<<PRZEDZIAL_zakres_maks<<"\n"<<endl;
   cout << "\t\tilosc_losowan->"<<ilosc_losowan<<endl;
   cout << "\t\tilosc_przedzialow->"<<ilosc_przedzialow<<endl;
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
    cout<<histogram[1]<<" "<<histogram[10]<<endl;
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
void array_histogra_to_file(string filename)
{
  //int arr*=histogram;
  ofstream myfile(filename);
  if(myfile.is_open())
  {
    for(int i=0;i<size_histogram;++i){ myfile << histogram[i]<<"\n";}
  }
  cout <<"Zapisano plik wynikowy historamu o nazwie: "<<filename<<endl;
}
//insert data to table
void data_generate()
{
for (int i=0; i<ilosc_losowan; i++)
{
    vectorint.push_back(random2());
}
cout <<"\t Wygenerowano tablice o rozmarze: "  <<ilosc_losowan<<endl;
}
int main ()
{
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

  cout<<histogram[1]<<" "<<histogram[10]<<endl;
  array_histogra_to_file("1watek.txt");

  //for (int i = 0; i < size_histogram; i++) {
  //      cout<< i<<"->"<<histogram[i]<<endl;
  //}
  //czyscimy tablice
  for (int i = 0; i < size_histogram; i++) {
        histogram[i] = '\0';

        
}

   for( i=0; i < NUM_THREADS; i++ ){
      cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].ilosc_w = NUM_THREADS;

      rc = pthread_create(&threads[i],NULL,THE_FUNCTION,(void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);

      }
    //pthread_detach(threads[i]);      
   }
   pthread_exit(NULL);
   cout<<"\t\t\t ***END THR***"<<endl;
   array_histogra_to_file("Nwatek.txt");
   



    for (int i = 0; i < size_histogram; i++) {
        cout<< i<<"->"<<histogram[i]<<endl;
  }
   cout<<"\t\t\t ***SAFE TO FILE***"<<endl;

   
   cout<<"\t\t\t ***END***"<<endl;
}

/*
Należy zbudować aplikację obliczającą histogram tablicy bajtów o podanej specyfikacji:
1. Aplikacja działa sekwencyjnie lub tworzy 2,4,8,10,12,14,16 wątków.
2. Rozmiar tablicy musi być nie mniejszy niż 4 mln bajtów.
3. Tablica danych wejściowych do wszystkich prób powinna być identyczna, czyli musi
4. być zapisywana w pliku.
5. Elementy są zliczane bezpośrednio do wspólnej tabeli histogramu o wymiarach 256
6. pól typu integer.
7. Należy dokonać pomiarów uśrednionego czasu obliczenia histogramu dla każdej
8. opcji programu.
9. Należy porównać czy wyniki są za każdym razem identyczne.
10. Dane wyjściowe (histogram) powinny być za każdym razem zapisywane w
oddzielnym pliku.
*/
