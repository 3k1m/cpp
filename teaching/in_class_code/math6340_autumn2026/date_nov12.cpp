#include<print>

class date{
private:
  int day, month, year;
  
public:
  date(int day_, int month_, int year_) : day(day_), month(month_), year(year_) {}


  void print() const {
      std::println("{}/{}/{}", day, month, year);
  }
  
  void advance() { // ignores leap years
      const int jan = 1, feb = 2, mar = 3, apr = 4, may = 5, jun = 6, jul = 7, aug = 8, sep = 9, oct = 10, nov = 11, dec = 12;
      
      if(month == sep or month == apr or month == jun or month == nov){ // has 30 days 
          if (day == 30){
              day = 1;
              ++month;
          }
          else{
            ++day;
          }
      }
      else if(month == jan or month == mar or month == may or month == jul or month == aug or month == oct){
          if(day == 31){
              day = 1;
              ++month;
          }
          else{
            ++day;
          }
      }
      else if(month==dec){
          if(day==31){
              day = 1;
              month = 1;
              ++year;
          }
          else{
              ++day;
          }
      }
      else if(month==feb){
          if(day==28){
              day = 1;
              ++month;
          }
          else{
            ++day;
          }
      }
      
  }
};

int main(){
    date d{1,1,2027};
    d.print();
    for(int i=0; i < 365; ++i){
        d.advance();
        d.print();
    }
    
    const date d2{1,1,2028};
    d2.print();
    //d2.advance();
    
}
