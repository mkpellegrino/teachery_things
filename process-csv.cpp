#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // std::sort
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

// for the log file
#include <fstream>
using namespace std;

class LaTeX_Header
{
public:
  LaTeX_Header(){};
  ~LaTeX_Header(){};
  void setColumns( int i ){ columns = i; };
  friend ostream& operator <<(ostream& out, const LaTeX_Header& l);
private:
  int columns;
};
ostream& operator <<(ostream& out, const LaTeX_Header& l)
{
  out << "\\documentclass[11pt]{article}" << endl;
  out << "\\usepackage[paper=landscape,total={10.5in,7.5in},top=0.5in]{geometry}" << endl;
  out << "\\usepackage{multicol}" << endl;
  
  out << "\\usepackage{pdflscape}" << endl;
  out << "\\usepackage{rotating}" << endl;
  out << "\\setlength{\\parskip}{0em}" << endl;
  out << "\\begin{document}" << endl;
  out << "%\\begin{landscape}" << endl;
  out << "\\pagenumbering{gobble}" << endl;
  out << "%\\begin{center}" << endl;
  
  out << "\\begin{tabular}{||";
  for( int i =0; i<l.columns; i++ )
    {
      if( i == 0 )
	{
	  // the first column is for name
	  out << " l ||";
	}
      else
	{
	  out << " c |";
	}
    }
  out << " }" << "\\hline \\hline" << endl;
  return out;
}


class LaTeX_Footer
{
public:
  LaTeX_Footer(){};
  ~LaTeX_Footer(){};
  friend ostream& operator <<(ostream& out, const LaTeX_Footer& l);
private:
  
};
ostream& operator <<(ostream& out, const LaTeX_Footer& l)
{
  out << "\\end{tabular}" << endl;
  out << "%\\end{landscape}" << endl;
  out << "\\end{document}" << endl;
  return out;
}

class Assignment
{
public:
  Assignment();
  Assignment( double d ){ score=d; };
  ~Assignment();
  string * getName(){ return name; };

  friend ostream& operator <<(ostream& out, const Assignment& a);

private:
  string * date;
  string * name;
  double score;
  int type; // 1 = formative    2 = summative
};

ostream& operator <<(ostream& out, const Assignment& a)
{
  out << a.score;
  return out;
}


class Student
{
public:
  Student(){};
  Student( string * l, string * f );
  ~Student();

  friend ostream& operator <<(ostream& out, const Student& s);

  void addAssignment( Assignment * a ){ assignments.push_back(a); };
private:
  string * last_name;
  string * first_name;
  vector<Assignment*> assignments;
};

ostream& operator <<(ostream& out, const Student& s)
{
  out << *s.last_name << ", " << *s.first_name << " & ";
  for( int i = 0; i<s.assignments.size(); i++ )
    {
      out << *s.assignments[i];
      if( i < s.assignments.size()-1 )
	{
	  out << " & ";
	}
	  
    }
  return out;
}

Student::~Student()
{
  delete last_name;
  delete first_name;
}

Student::Student( string * l, string * f )
{
  last_name = l;
  first_name = f;
}

int main(int argc, char *argv[])
{
  if( argc < 3 )
    {
      cerr << "you must supply an input and an output filename" << endl;
      cerr << "ex: " << argv[0] << " input.csv " << " " << "output.tex" << endl;
      exit(-1);
    }
  if( string(argv[1]) == string(argv[2]) )
    {
      cerr << "you must supply an input and an output filename THAT HAS A DIFFERENT NAME" << endl;
      cerr << "ex: " << argv[0] << " grades.csv gradereport.tex" << endl;
      exit(-1);
    }


  
  LaTeX_Header * header = new LaTeX_Header();
  LaTeX_Footer * footer = new LaTeX_Footer();
  vector<Student*> student;
  vector<string*> label;
  //ifstream infile( "test.csv" );
  //ifstream infile( "grades.csv" );
  ifstream infile( argv[1] );
  
  ofstream latex_out;
  //latex_out.open( "output.tex" );
  latex_out.open( argv[2] );

  string line;

  // throw out the header
  getline( infile, line, '\n');
  stringstream labels(line);
  while(labels.good())
    {
      string substr0;
      getline(labels, substr0, ',');
      label.push_back( new string(substr0) );
    }

#ifdef DEBUG
  cerr << "There are " << label.size() << " labels." << endl;
  for( int i=0; i<label.size(); i++ )
    {
      cout << *label[i] << endl;
    }
#endif
  
  header->setColumns( label.size()-4 );
  int ln = 0;
  //while (infile)
  string f;
  string l;
  string g;
  string e;
  while( getline(infile, f,',' ) && getline(infile,l,',') && getline(infile,e,',') && getline(infile,e,',') && getline(infile, g,'\n' ) )
    {
      //getline(infile, line,'\n' );

      // remove the double quotes
      f.erase(remove(f.begin(), f.end(), '\"'), f.end());
      l.erase(remove(l.begin(), l.end(), '\"'), l.end());
      
      Student * s = new Student( new string(l), new string(f) );

      // process the grades here
      stringstream grades(g);
      while(grades.good())
	{
	  string substr;
	  getline(grades, substr, ','); //get first string delimited by comma
#ifdef DEBUG
	  cout << substr << " ";
#endif
	  if( substr == string("-")  )
	    {
	      s->addAssignment( new Assignment( 0.0 ));
	    }
	  else
	    {
	      if( stod(substr.c_str()) < 100 )
		{
		  s->addAssignment( new Assignment(stod(substr.c_str())) );
		}
	    }
		
	}

      student.push_back(s);
      
      if( g != string("")) 
	cout << "(" << ++ln << ") " << f << " " << l << " " << g << endl;
    }
  
  if (!infile.eof())
    {
      cerr << "File Error!\n";
      exit(-1);
    }

  latex_out << *header << endl;
  latex_out << "\\( \\ \\) & ";

  // Process the Labels at the Top
  for( int i=4; i<label.size()-1; i++ )
    {
      // remove the extra stuff in the labels
      label[i]->erase(remove(label[i]->begin(), label[i]->end(), '\"'), label[i]->end());
      //label[i]->erase(remove(label[i]->begin(), label[i]->end(), "?"), label[i]->end());

      string s = "Quiz: ";
      string::size_type j = label[i]->find(s);
      if (j != string::npos) label[i]->erase(j, s.length());

      s = string( " (Real)" );
      j = label[i]->find(s);
      if (j != string::npos) label[i]->erase(j, s.length());
      
      latex_out << "\\begin{turn}{90} ";
      replace( label[i]->begin(), label[i]->end(), '&', '+');
      latex_out << *label[i];
      
      //latex_out << " T ";
      latex_out << " \\end{turn}";
      if( i < label.size()-2 )
	{
	  latex_out << " & ";
	}
      else
	{
	  latex_out << " \\\\ \\hline" << endl;
	}
    }
  for( int i=0; i<student.size(); i++ )
    {
      latex_out << *student[i] << "\\\\ \\hline" << endl;
    }
  latex_out << *footer <<  endl;
  return 0;
}


