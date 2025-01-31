#include <iostream>
#include <vector>
using namespace std;
bool first_last=false;

class Block
{
public:
  Block( string l )
  {
    letter = l;
    teacher_name = "Mr. Pellegrino";
    location = "Room 452";
    switch( l[0] )
      {
      case 'A':
	title = "AP Calc AB : 350-002";
	break;
      case 'B':
	title = "Hon. Precalc : 340-01";
	break;
      case 'C':
	title = "AP Calc AB : 350-01";
	break;
      case 'D':
	title = "Prep Period";
	break;
      case 'E':
	title = "Hon. Precalc : 340-009";
	break;
      case 'F':
	title = "Prep Period";	
	break;
      case 'G':
	title = "Robotics : 455-003";
	break;
      case 'H':
	title = "Culinary Hallway Duty";
	break;
      case 'V':
	title = "Advisory";
	break;
      }
    
    switch( l[0] )
      {
      case 'A':
      case 'E':
	morning_start_time = string( "8:15" );
	morning_end_time = string( "9:39" );
	advisory_start_time = string("8:15");
	advisory_end_time = string("9:28");
	break;
      case 'B':
      case 'F':
	morning_start_time = string( "9:43" );
	morning_end_time = string( "11:07" );
	advisory_start_time = string("10:16");
	advisory_end_time = string("11:29");
	break;

      case 'C':
      case 'G':
	morning_start_time = string( "11:11" );
	morning_end_time = string( "12:35" );
	advisory_start_time = string("11:33");
	advisory_end_time = string("12:46");
	break;

      case 'D':
      case 'H':
	morning_start_time = string( "1:09" );
	morning_end_time = string( "2:33" );
	advisory_start_time = string("1:20");
	advisory_end_time = string("2:33");
	break;

      case 'V':
	morning_start_time = string( "9:32" );
	morning_end_time = string( "10:12" );
	advisory_start_time = string("");
	advisory_end_time = string("");
      }

    afternoon_start_time = string( "" );
    afternoon_end_time = string( "" );
    
  }
  Block()
  {
    letter = "?";
    title = "invalid";
    morning_start_time = "invalid";
    morning_end_time = "invalid";
    afternoon_start_time = "invalid";
    afternoon_start_time = "invalid";
  };
  ~Block()
  {
  }

  string getTitle(){ return title; };
  string getMorningTime(){ return (morning_start_time+string("-")+morning_end_time); };
  string getAfternoonTime(){ return (afternoon_start_time+string("-")+afternoon_end_time); };
  string getAdvisoryTime(){ return (advisory_start_time+string("-")+advisory_end_time); };
  friend ostream &operator << (ostream &out, const Block &s); 

private:
  string letter;
  string title;
  string morning_start_time;
  string morning_end_time;
  string afternoon_start_time;
  string afternoon_end_time;
  string advisory_start_time;
  string advisory_end_time;
  string teacher_name;
  string location;
};


ostream & operator << (ostream &out, const Block &b)
{
  out << b.title << " - " << b.letter << " Block";
  return out;
}
class Student
{
public:
  Student()
  {
    full_name=string("invalid");
    first_name=string("invalid");
    last_name=string("invalid");
    block=string("invalid");
    cohort=0;
    yog=-1;
  };
  ~Student(){};

  Student( string ln, string fn, int c, string crs, int y )
  {
    full_name=string( ln + ", " + fn );
    last_name = ln;
    first_name = fn;
    cohort=c;
    block=crs;
    yog=y;
  };
  
  string getFirstName(){return first_name;};
  string getLastName(){return last_name;};
  string getBlock(){return block;};
  int getCohort(){return cohort;};
  string getFullName(){return full_name;};
  int getYOG(){ return yog; };
  friend ostream &operator << (ostream &out, const Student &s); 
private:
  string full_name;
  string first_name;
  string last_name;
  string block;
  int cohort;
  int yog;
};



ostream & operator << (ostream &out, const Student &s)
{
  if( first_last )
    {
      out << s.first_name << " " << s.last_name << ": ";
      switch( s.yog )
	{
	case 2028:
	  out << "Freshman";
	  break;
	case 2027:
	  out << "Sophomore";
	  break;
	case 2026:
	  out << "Junior";
	  break;
	case 2025:
	  out << "Senior";
	  break;
	default:
	  out << "Unknown";
	}
    }
  else
    {
      out << s.full_name;
    }
  return out;
}

vector<Student> student_vector;
vector<Student> seating_vector;
vector<Block> block_vector;


int blockSize(string block)
{
  int retVal=0;
  for( int i=0; i<student_vector.size(); i++ )
    {
      if( student_vector[i].getBlock() == block ) retVal++;
    }
  return retVal;
  
}



bool compareStudentLastNames(Student s1, Student s2)
{
  if( s1.getLastName() == s2.getLastName() )
    {
      return( s1.getFirstName() < s2.getFirstName() );
    }
  return (s1.getLastName() < s2.getLastName());
}
bool compareStudentFirstNames(Student s1, Student s2)
{
  if( s1.getFirstName() == s2.getFirstName() )
    {
      return ( s1.getLastName() < s2.getLastName() );
    }
  return (s1.getFirstName() < s2.getFirstName());
}
bool compareCohorts(Student s1, Student s2)
{
  return (s1.getCohort() < s2.getCohort());
}
bool compareBlocks(Student s1, Student s2)
{
  return (s1.getBlock() < s2.getBlock());
}

string p( int s )
{
  // format the student name for the table
  string retVal;
  if( seating_vector.size() < s )
    {
      retVal=string("Empty");
    }
  else
    {
      // if the name is long, make it spread over 2 lines
      //retVal = seating_vector[s].getFirstName() + string(" ") + seating_vector[s].getLastName();
      //if( retVal.length() > 15 ) retVal = "\\begin{tabular}[c]{@{}c@{}}" + seating_vector[s].getFirstName() + string(" \\\\ ") + seating_vector[s].getLastName() + "\\end{tabular}";
      retVal = "\\begin{tabular}[c]{@{}c@{}}" + seating_vector[s].getFirstName() + string(" \\\\ ") + seating_vector[s].getLastName() + "\\end{tabular}";
      //retVal=seating_vector[s].getFirstName() + string(" ") + seating_vector[s].getLastName();
    }
  return retVal;
}

string getSeatNumber( string block )
{
  string retVal = string("");
  return retVal;
}

void seatingChart( string block, int day )
{
  Block b = Block( block );
  cout << "\\begin{center}" << endl;
  //cout << "\\begin{tabular}{|| c c | c c | c c | c c | c c ||}" << endl;
  cout << "\\begin{tabular}{|| c c | c c | c c | c c ||}" << endl;
  cout << "\\hline \\hline" << endl;
  //cout << "\\multicolumn{10}{|| c ||}{\\textbf{" << b << " - Seating Chart}} \\\\" << endl;
  cout << "\\multicolumn{8}{|| c ||}{\\textbf{" << b << " - Seating Chart}} \\\\" << endl;
  cout << "\\hline \\hline" << endl;
  

  //sort(student_vector.begin(), student_vector.end(), compareStudentLastNames);
  
  for( int i=0; i<student_vector.size(); i++ )
    {
      int cohort=student_vector[i].getCohort();
      string b=student_vector[i].getBlock();

      // This was a leftover from when students
      // didn't attend in-person on their cohort day
      //if( cohort!=day && b==block )
      if( b==block )
	{
	  seating_vector.push_back( student_vector[i] );
	}
    }

  
  int l = seating_vector.size();

  // buffer the seating arrangement with empty seats
  while( seating_vector.size() < 32 )
    {
      seating_vector.push_back(Student("\\textit{Empty}", "", day+1, block, -1));
    }
  
#ifdef DEBUG
  cerr << "Number of occupied seats: " << l << endl;
#endif

  first_last=true;


  int newrow = 8;
  //int newrow = 10;
  //for( int i = 29; i>=0; i-- )
  for( int i = 31; i>=0; i-- )
    {
      cout << p(i);
      newrow--;
      if( newrow == 0 )
	{
	  // 20240831 - mkpellegrino
	  //newrow = 10;
	  newrow = 8;

	  //cout << p(25) << "\\\\" << endl;
	  cout << "\\\\" << endl;
	  cout << "\\hline" << endl;
	}
      else
	{
	  cout << " & ";
	}

    }
  
  // for( int i = 26; i>=0; i-=6 )
  //   {
  //     for( int j=i+5; j>=i; j-- )
  // 	{
  // 	  cout << p(j);
  // 	  if( j>i ) cout << " & ";
  // 	}
  //     cout << "\\\\" << endl;
  //     cout << "\\hline" << endl;
  //   }

  // cout << p(25) << "\\\\" << endl;


  first_last=false;

  //cout << "\\hline \\hline" << endl;
  cout << "\\hline" << endl;
  cout << "\\end{tabular}" << endl;
  cout << "\\par{} \\noindent \\textit{Front of Classroom}" << endl;
  cout << "\\end{center}" << endl;
  return;
}


void inperson( string block, int day )
{

  if( blockSize(block) == 0 ) return;
  
  //sort(student_vector.begin(), student_vector.end(), compareStudentLastNames);
  
  cout << "\\begin{enumerate}" << endl;
  cout << "\\setlength\\itemsep{0em}" << endl;

  for( int i=0; i<student_vector.size(); i++ )
    {
      int cohort=student_vector[i].getCohort();
      string b=student_vector[i].getBlock();
      
      if( cohort!=day && b==block )
	{
	  if( student_vector[i].getLastName() != "\\textit{Empty}" )
	    cout << "\\item " << student_vector[i] << endl;
	}
    }
  cout << "\\end{enumerate}" << endl;  
  return;
}


void remote( string block, int day )
{
  first_last = true;
  if( blockSize(block) == 0 ) return;
  cout << "\\begin{itemize}" << endl;
  cout << "\\setlength\\itemsep{0em}" << endl;
  //sort(student_vector.begin(), student_vector.end(), compareStudentFirstNames);

  for( int i=0; i<student_vector.size(); i++ )
    {
      int cohort=student_vector[i].getCohort();
      string b=student_vector[i].getBlock();
      
      if( cohort==day && b==block )
	{
	  if( student_vector[i].getLastName() != "\\textit{Empty}" ) cout << "\\item " << student_vector[i] << endl;
	}
    }
  cout << "\\end{itemize}" << endl;  
  first_last = false;
  return;
}

void afternoon( string block )
{
  first_last = true;

  if( blockSize(block) == 0 ) return;
  
  cout << "\\begin{enumerate}" << endl;
  cout << "\\setlength\\itemsep{0em}" << endl;
  //sort(student_vector.begin(), student_vector.end(), compareStudentLastNames);

  for( int i=0; i<student_vector.size(); i++ )
    {
      string b=student_vector[i].getBlock();
      
      if( b==block )
	{
	  if( student_vector[i].getLastName() != "\\textit{Empty}" )
	    cout << "\\item " << student_vector[i] << endl;
	}
    }
  cout << "\\end{enumerate}" << endl;  
  first_last = false;
  return;


}
int count( string s, int p )
{
  // count by yog or cohort
  int return_value=0;
  for( int i=0; i<student_vector.size(); i++ )
    {
      if( student_vector[i].getLastName() != "\\textit{Empty}" )
	{
	  if( s == "yog" && p == student_vector[i].getYOG() ) return_value++;
	  if( s == "cohort" && p == student_vector[i].getCohort() ) return_value++;
	}
    }
  return return_value;
}

int count( string s, string p )
{
  // count by block
  int return_value=0;
  for( int i=0; i<student_vector.size(); i++ )
    {
      if( student_vector[i].getLastName() != "\\textit{Empty}" )
	{
	  if( s == "block" && p == student_vector[i].getBlock() ) return_value++;
	}
    }
  return return_value;
}



int main(int argc, char *argv[])
{  

  student_vector.push_back(Student("\\textit{Empty}","",1,"A",2028));
  student_vector.push_back(Student("Fakename1","Fakename",1,"A",2025));
  student_vector.push_back(Student("Fakename2","Fakename",1,"A",2026));
  student_vector.push_back(Student("Fakename3","Fakename",1,"A",2025));
  student_vector.push_back(Student("Fakename4","Fakename",1,"A",2025));
  student_vector.push_back(Student("Fakename5","Fakename",1,"A",2025));
  student_vector.push_back(Student("Fakename6","Fakename",1,"A",2025));
  student_vector.push_back(Student("Fakename7","Fakename",1,"A",2026));
    student_vector.push_back(Student("\\textit{Empty}","",1,"B",2028));
  student_vector.push_back(Student("Fakename8","Fakename",1,"A",2025));
  student_vector.push_back(Student("Fakename9","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameA","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameB","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameC","Fakename",1,"A",2026));
  student_vector.push_back(Student("FakenameD","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameE","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameF","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameG","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameH","Fakename",1,"A",2026));
    student_vector.push_back(Student("\\textit{Empty}","",1,"B",2028));

  student_vector.push_back(Student("FakenameI","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameJ","Fakename",1,"A",2025));
  student_vector.push_back(Student("FakenameK","Fakename",1,"A",2025));



  student_vector.push_back(Student("\\textit{Empty}","",1,"B",2028));
  student_vector.push_back(Student("Fakename1","Fakename",1,"B",2027));
  student_vector.push_back(Student("Fakename2","Fakename",1,"B",2026));
  student_vector.push_back(Student("Fakename3","Fakename",1,"B",2027));
  student_vector.push_back(Student("Fakename4","Fakename",1,"B",2027));
  student_vector.push_back(Student("Fakename5","Fakename",1,"B",2027));
  student_vector.push_back(Student("\\textit{Empty}","",1,"B",2028));
  student_vector.push_back(Student("Fakename6","Fakename",1,"B",2027));
  student_vector.push_back(Student("Fakename7","Fakename",1,"B",2026));
  student_vector.push_back(Student("Fakename8","Fakename",1,"B",2027));
  student_vector.push_back(Student("Fakename9","Fakename",1,"B",2027));
  student_vector.push_back(Student("FakenameA","Fakename",1,"B",2027));
  student_vector.push_back(Student("\\textit{Empty}","",1,"B",2028));
  student_vector.push_back(Student("FakenameB","Fakename",1,"B",2027));
  student_vector.push_back(Student("FakenameC","Fakename",1,"B",202));
  student_vector.push_back(Student("FakenameD","Fakename",1,"B",2027));
  student_vector.push_back(Student("FakenameE","Fakename",1,"B",2027));
  student_vector.push_back(Student("FakenameF","Fakename",1,"B",2027));
  student_vector.push_back(Student("FakenameG","Fakename",1,"B",2027));


  
  student_vector.push_back(Student("\\textit{Empty}","",1,"C",2028));
  student_vector.push_back(Student("Fakename1","Fakename",1,"C",2025));
  student_vector.push_back(Student("Fakename2","Fakename",1,"C",2026));
  student_vector.push_back(Student("Fakename3","Fakename",1,"C",2025));
  student_vector.push_back(Student("Fakename4","Fakename",1,"C",2025));
  student_vector.push_back(Student("Fakename5","Fakename",1,"C",2025));
  student_vector.push_back(Student("Fakename6","Fakename",1,"C",2025));
  student_vector.push_back(Student("Fakename7","Fakename",1,"C",2026));
  student_vector.push_back(Student("Fakename8","Fakename",1,"C",2025));
  student_vector.push_back(Student("Fakename9","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameA","Fakename",1,"C",2025));
  student_vector.push_back(Student("\\textit{Empty}","",1,"C",2028));
  student_vector.push_back(Student("FakenameB","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameC","Fakename",1,"C",2026));
  student_vector.push_back(Student("FakenameD","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameE","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameF","Fakename",1,"C",2025));
  student_vector.push_back(Student("\\textit{Empty}","",1,"C",2028));
  student_vector.push_back(Student("FakenameG","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameH","Fakename",1,"C",2026));
  student_vector.push_back(Student("FakenameI","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameJ","Fakename",1,"C",2025));
  student_vector.push_back(Student("FakenameK","Fakename",1,"C",2025));



  
  student_vector.push_back(Student("\\textit{Empty}","",1,"E",2028));
  student_vector.push_back(Student("Fakename1","Fakename",1,"E",2025));
  student_vector.push_back(Student("Fakename2","Fakename",1,"E",2026));
  student_vector.push_back(Student("Fakename3","Fakename",1,"E",2025));
  student_vector.push_back(Student("Fakename4","Fakename",1,"E",2025));
  student_vector.push_back(Student("Fakename5","Fakename",1,"E",2025));
  student_vector.push_back(Student("Fakename6","Fakename",1,"E",2025));
    student_vector.push_back(Student("\\textit{Empty}","",1,"E",2028));

  student_vector.push_back(Student("Fakename7","Fakename",1,"E",2026));
  student_vector.push_back(Student("Fakename8","Fakename",1,"E",2025));
  student_vector.push_back(Student("Fakename9","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameA","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameB","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameC","Fakename",1,"E",2026));
  student_vector.push_back(Student("FakenameD","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameE","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameF","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameG","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameH","Fakename",1,"E",2026));
  student_vector.push_back(Student("FakenameI","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameJ","Fakename",1,"E",2025));
  student_vector.push_back(Student("FakenameK","Fakename",1,"E",2025));



  
  student_vector.push_back(Student("\\textit{Empty}","",1,"G",2028));
  student_vector.push_back(Student("Fakename1","Fakename",1,"G",2025));
  student_vector.push_back(Student("Fakename2","Fakename",1,"G",2026));
  student_vector.push_back(Student("Fakename3","Fakename",1,"G",2025));
  student_vector.push_back(Student("Fakename4","Fakename",1,"G",2025));
  student_vector.push_back(Student("Fakename5","Fakename",1,"G",2025));
  student_vector.push_back(Student("Fakename6","Fakename",1,"G",2025));
  student_vector.push_back(Student("Fakename7","Fakename",1,"G",2026));
  student_vector.push_back(Student("Fakename8","Fakename",1,"G",2025));
  student_vector.push_back(Student("\\textit{Empty}","",1,"G",2028));
  student_vector.push_back(Student("Fakename9","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameA","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameB","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameC","Fakename",1,"G",2026));
  student_vector.push_back(Student("FakenameD","Fakename",1,"G",2025));
  student_vector.push_back(Student("\\textit{Empty}","",1,"G",2028));
  student_vector.push_back(Student("FakenameE","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameF","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameG","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameH","Fakename",1,"G",2026));
  student_vector.push_back(Student("FakenameI","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameJ","Fakename",1,"G",2025));
  student_vector.push_back(Student("FakenameK","Fakename",1,"G",2025));


  
  student_vector.push_back(Student("\\textit{Empty}","",1,"V",2028));
  student_vector.push_back(Student("Fakename1","Fakename",1,"V",2028));
  student_vector.push_back(Student("Fakename2","Fakename",1,"V",2028));
  student_vector.push_back(Student("Fakename3","Fakename",1,"V",2028));
  student_vector.push_back(Student("Fakename4","Fakename",1,"V",2028));
  student_vector.push_back(Student("Fakename5","Fakename",1,"V",2028));
  student_vector.push_back(Student("Fakename6","Fakename",1,"V",2028));
  student_vector.push_back(Student("Fakename7","Fakename",1,"V",2028));
  
  
  /* seating block day */
  if( argc < 2 || argc > 3 )
    {
      cerr << "[ usage error: " << argv[0] << " block ]" << endl;
      return(-1);
    }
  
  if( (argv[1][0] !='A' && argv[1][0] != 'B' && argv[1][0] != 'C' && argv[1][0] !='D' && argv[1][0] !='E' && argv[1][0] !='F' && argv[1][0] != 'G' && argv[1][0] != 'H' && argv[1][0] != 'V') && argv[1][0] != 'X' )
    {
      cerr << "[ argument error: " << argv[0] << " A|B|C|D|E|F|G|H|V ]" << endl;
      return(-1);
    }

  //cout << "\\documentclass[11pt]{article}" << endl;
  cout << "\\documentclass[12pt]{article}" << endl;
  cout << "\\usepackage[letterpaper,total={7.5in,10.5in},top=0.5in]{geometry}" << endl;
  cout << "\\usepackage{multicol}" << endl;
  cout << "\\setlength{\\parskip}{0em}" << endl;
  cout << "\\begin{document}" << endl;
  cout << "\\pagenumbering{gobble}" << endl;

  if( argv[1][0] == 'X' )
    {
      block_vector.push_back(Block("A"));
      block_vector.push_back(Block("B"));
      block_vector.push_back(Block("C"));
      block_vector.push_back(Block("D"));
      block_vector.push_back(Block("E"));
      block_vector.push_back(Block("F"));
      block_vector.push_back(Block("G"));
      block_vector.push_back(Block("H"));
      block_vector.push_back(Block("V"));
    }
    
  Block b = Block( string(argv[1]));

  //cout << "\\section*{} \\textbf{" << b << "}" << endl;
  //cout << "\\par{} \\textbf{" << b.getMorningTime() << "}" << endl;

  cout << "\\section*{} \\textbf{" << b << " \\ \\ \\ \\ \\ " << b.getMorningTime() << " \\ \\ \\ \\ \\ (" <<  b.getAdvisoryTime() << ")}" << endl;


  first_last=true;

  
  
  afternoon( argv[1] );
  //cout << "\\end{multicols}" << endl;

  seatingChart( argv[1], 1 );

  cout << "\\end{document}" << endl;
  return 0;
}

