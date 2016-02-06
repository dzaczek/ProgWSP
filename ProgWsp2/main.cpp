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

#include <sys/stat.h>
#include <sstream>



using namespace std;

//#define NUM_THREADS     4
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

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

static int ilosc_przedzialow = SIZE_ARRAY;
static int size_histogram = SIZE_ARRAY;
static int zakres_liczb = 8192;
static long long int ilosc_losowan = 4000000; //100000000;
static int rozmiar_p = zakres_liczb / ilosc_losowan;
vector<int>  vectorint;
//std::array <int,SIZE_ARRAY> histogram;
int histogram[SIZE_ARRAY];

string filename_data = "orginal.txt";
int NUM_THREADS = 32; //16384;
int iloscprobek = 4;

time_t rawtime;
struct tm * timeinfo;
char buffer[80];


class statsy
{
public:
  int numer_pomiaru;
  int ilosc_watkow;
  double czas_wykonywania;
  int hitt[256];

  statsy();
  ~statsy();
  
};



static timestamp_t get_timestamp()
{
  struct timeval now;
  gettimeofday (&now, NULL);
  return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}




struct thread_data
{ int  thread_id;
  int ilosc_w;

};

void *THE_FUNCTION(void *threadarg)
{
  struct thread_data *my_data;
  my_data = (struct thread_data *) threadarg;
  int PRZEDZIAL_rozmiar = ilosc_losowan / my_data->ilosc_w;
  int PRZEDZIAL_zakres_min = PRZEDZIAL_rozmiar * my_data->thread_id;
  int PRZEDZIAL_zakres_maks = PRZEDZIAL_zakres_min + PRZEDZIAL_rozmiar;
  int *wsk_array_hist;
  wsk_array_hist = histogram;
  for (long long int sek = PRZEDZIAL_zakres_min; sek < PRZEDZIAL_zakres_maks; ++sek)
  {


    long long numerprzedzialu = (vectorint[sek] * ilosc_przedzialow - 1) / zakres_liczb;
    //cout <<"\t\tID: " << my_data->thread_id<< " numerprzedzialu"  <<  numerprzedzialu<< endl;
    //cout <<"\t\tID: " << my_data->thread_id<< " sek"  <<  sek<< endl;
    //wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
    if (numerprzedzialu < ilosc_przedzialow && numerprzedzialu >= 0) {
      wsk_array_hist[numerprzedzialu] = wsk_array_hist[numerprzedzialu] + 1;

      // wsk_array_hist[numerprzedzialu]=wsk_array_hist[numerprzedzialu]+1;
      // cout << numerprzedzialu << " " << histogram[numerprzedzialu] << " "<< w0pk <<endl;
    }
    else
    {
      cout << "numerprzedzialu ->" << numerprzedzialu;

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
  while (inputFile >> invar) {
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
  int rozmiar_p = zakres_liczb / ilosc_losowan;

  int w0pk;
  int b;

  for (auto w0pk : vectorint)
  {

    int numerprzedzialu = (w0pk * ilosc_przedzialow - 1) / zakres_liczb;
    //numerprzedzialu=numerprzedzialu;
    //cout <<numerprzedzialu <<" ";
    if (numerprzedzialu < size_histogram && numerprzedzialu >= 0) {
      histogram[numerprzedzialu] = histogram[numerprzedzialu] + 1;
      // cout << numerprzedzialu << " " << histogram[numerprzedzialu] << " "<< w0pk <<endl;
    }
    else
    {
      cout << "numerprzedzialu ->" << numerprzedzialu;
    }

  }


}


int createSumArray(int* arr, int size)
{
  int wynik = 0;
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
  if (myfile.is_open())
  {
    for (int i = 0; i < size_histogram; ++i) { myfile << i + 1 << "\t" << histogram[i] << "\n";}
  }
//  cout <<"Zapisano plik wynikowy historamu o nazwie: "<<filename<<endl;
}

void string_to_file(string filename, string data)
{
  //int arr*=histogram;
  ofstream myfile(filename, std::ios::app);
  if (myfile.is_open())
  {
    myfile << data;
  }
  else
  {
    cout << "***FUCK" << endl;
  }
//  cout <<"Zapisano plik wynikowy historamu o nazwie: "<<filename<<endl;
}
//insert data to table
void data_generate()
{
  for (long long int i = 0; i < ilosc_losowan; i++)
  {
    vectorint.push_back(random2());
  }
  cout << "\t Wygenerowano tablice o rozmarze: "  << ilosc_losowan << endl;
}
int main ()
{
  //cout << "**** max_size: " << vectorint.max_size() << "\n";
  cout << "*** PID: " << getpid() << endl;
  sleep (3);
  pthread_t threads[NUM_THREADS];
  struct thread_data td[NUM_THREADS];
  srand(time(NULL));
  int rc;
  int i;
  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, 80, "%Y-%m-%d_%I:%M:%S", timeinfo);
  std::string str77(buffer);
  //  std::cout << str77<<endl;

  //char str78=buffer;



  //generujemy vector losowych danych z zakresu
  if (!check_if_file_exist(filename_data)) {
    data_generate();
    outputVint(vectorint, filename_data);
  }
  else
  {
    inputVint(filename_data);
    cout << "plik istnial zaladowano dane z pliku: " << filename_data << endl;
    // cout <<vectorint[1]<<vectorint[10]<<vectorint[15]<<endl;
  }

  //tworzymy histogram
  tworzHistogram();


  array_histogra_to_file("wzor.txt");

  //for (int i = 0; i < size_histogram; i++) {
  //      cout<< i<<"->"<<histogram[i]<<endl;
  //}
  //czyscimy tablice

  for (int rotator = 1; rotator <= iloscprobek; rotator++) {

    string str76 = str77 + "_" + to_string(rotator);
    int NUM_THREADS_S=NUM_THREADS;

    char str75[21];
    size_t length = str76.copy(str75, str76.length());
    cout << "length" << length << endl;
   // str75[length] = "\0";

    const int dir_err = mkdir(str76.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (-1 == dir_err)
    {
      printf("Error creating directory!n");
      exit(1);
    }




    for (int i = 0; i < size_histogram; i++) {
      histogram[i] = '\0';


    }
    string head = "|THREADS|CORE TIME|Timestamp| Chrono | Ele Hist| TIME/CORE |NUM/THREADS|";
    string head1 = ";THREADS;CORE TIME;Timestamp; Chrono ; Ele Hist; TIME/CORE ;NUM/THREADS;\n";

    cout << "-----------------------------------------------------------------------" << endl;
    cout << head << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    string_to_file(str76 + "/STATS.csv", head1);
    while (NUM_THREADS_S >= 1)
    {
//  cout<<"\t\t\t ***START THR***"<<" \tNR: "<<NUM_THREADS <<endl;
      clock_t begin = clock();
      timestamp_t t0 = get_timestamp();
      auto start = std::chrono::steady_clock::now();
      for ( i = 0; i < NUM_THREADS_S; i++ ) {
        //cout <<"main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].ilosc_w = NUM_THREADS_S;

        rc = pthread_create(&threads[i], NULL, THE_FUNCTION, (void *)&td[i]);
        if (rc) {
          cout << "Error:unable to create thread," << rc << endl;
          exit(-1);

        }
        // pthread_detach(threads[i]);
      }
      for (i = 0; i < NUM_THREADS_S; i++)pthread_join(threads[i], NULL);
      // cout <<"test" <<pthread_exit(NULL)<<endl;
      timestamp_t t1 = get_timestamp();
      clock_t end = clock();
      auto stop = std::chrono::steady_clock::now();

//for(i=0; i<NUM_THREADS_S; i++)
      //  {
      //         status*   status;
      //        pthread_join(threads[i], &status);
      //}

      double elapsed_seconds = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
      string s = to_string(NUM_THREADS_S);
      double secs = (t1 - t0) / 1000000.0L;
      double diffcores = diffclock(begin, end);
      double diffcore = diffcores / NUM_THREADS_S;
      int iloscnawatek = ilosc_losowan / NUM_THREADS_S;
      //cout<< "|"<<NUM_THREADS <<"|"<<diffclock(begin,end)<<"|"<< secs<<"|"<<elapsed_seconds<<"|"<< createSumArray(histogram,SIZE_ARRAY) <<"|"<<endl;
      printf("|%7d|%9f|%9f|%s%5f%s|%s%9d%s|%11f|%s%11u%s|\n", NUM_THREADS_S, diffcores, secs, KGRN, elapsed_seconds / 1000000000, KNRM, KBLU, createSumArray(histogram, SIZE_ARRAY), KNRM, diffcore, KBLU, iloscnawatek, KNRM);
      cout << "-----------------------------------------------------------------------" << endl;
      std::ostringstream mydane;

      mydane << ";" << NUM_THREADS_S << ";" << diffcores << ";" << secs << ";" << elapsed_seconds / 1000000000 << ";" << createSumArray(histogram, SIZE_ARRAY) << ";" << diffcore << ";" << iloscnawatek << ";\n";

      string_to_file(str76 + "/STATS.csv", mydane.str());
//   cout<<"\t\t\t ***END THR***"<<endl;
      array_histogra_to_file(str76 + "/" + s + "watek.txt");

      const int pki = (NUM_THREADS_S <= 4) ? NUM_THREADS_S = NUM_THREADS_S - 1 : NUM_THREADS_S = NUM_THREADS_S / 2;

      for (int i = 0; i < size_histogram; i++) {
        histogram[i] = '\0';
      }


    }

  }


  //for (int i = 0; i < size_histogram; i++) {
  //    cout<< i<<"->"<<histogram[i]<<endl;
  //}
  //cout<<"\t\t\t ***SAFE TO FILE***"<<endl;

  // cout <<isprint(timestart)<<endl;

  cout << "\t\t\t ***END***" << endl;
  //auto gooo="cd "+str77+"/";
  //system("cd str77");
  // char cmd=;
  //system("gnuplot;reset;set term png truecolor;set term png size 1600, 400;set output 'profit_dots.png';set xlabel 'ZAKRES';set ylabel 'WARTOSCI';set grid;set boxwidth 1.95 relative;set style fill transparent solid 0.5 noborder;list=system('ls -1B *watek.txt | sort -h');plot for[file in list] file  using 1:2 w points  title  file; exit;");
  //return 0;
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
