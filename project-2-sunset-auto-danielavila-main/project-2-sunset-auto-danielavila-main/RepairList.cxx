#include <string>     // string
#include <fstream>
#include <iterator>   // next()
#include <stdexcept>  // invalid_argument
#include <forward_list>
#include <list>

#include "RepairList.hpp"

using std::string;
using std::ifstream;

/**********************************************
**  Public/private implementations, types, and objects
** for class BookList
************************************************/

/*************************************
**  Friend functions: read and write
**************************************/

std::ostream & operator<<( std::ostream & stream, const RepairList & repairlist )
{
	for( const auto & request : repairlist._dailyList )   stream << '\n' << std::setw(5) << request;
	
	return stream;
}


std::istream & operator>>( std::istream & stream, RepairList & repairlist )
{
	Repair request;

	while(stream) {
		stream >> request;
		repairlist.addToList(std::move(request));
	}

	return stream;
}

/***********************
** Constructor
************************/
// TO DO
RepairList::RepairList() = default; //automatically determines what should be initialized 

/*********************
** Destructor
*********************/
// TO DO
RepairList::~RepairList() = default; //automatically determines what is deleted 

/************************
** Assignment operator
************************/
// TO DO
RepairList & RepairList::operator+=( const RepairList & rhs)
{
	// Concatenate the right hand side list of repair requests to this list by repeatedly adding 
	//each repair at the end of the current repair list 
	
	std::list<Repair>::const_iterator current;

	for (current = rhs._dailyList.begin(); current != rhs._dailyList.end(); ++current) //iterator starts at beginning of list; iterator != end of rhs list; increment the iterator
	{
		addToList(*current); //the iterator is added to the rhs of the list in order to concatenate the lhs and rhs
	}
	return (*this); //all assignment operators return (*this)
}

/***********************
** Queries or getters
************************/
// If you decide to use std::forward_list, keep in mind that some implementations of a singly linked
//list maintain the size (number of elements in the list).  // std::forward_list does not. The size of
//singly linked list must be calculated on demand by walking the list from beginning to end counting
//the number of elements visited.  The STL's std::distance() function does that, or you can write
//your own loop.

//TO DO
// return the size of the list
std::size_t RepairList::size() const
{
	// return the size of the list
	return _dailyList.size();			//returns the number of repairs in the list
}

// TO DO
// return the current repair
Repair RepairList::currRepair() const
{
	return (*_nowServicing);			//dereferences the value it is pointing to; value in the current repair
}

/***********************
** Mutators
************************/

// read the list of advanced repair requests from
// the specified file
void RepairList::loadAdvanceList( const std::string& filename )
{
  std::ifstream inFile(filename);
  Repair newRequest;

  if( inFile.is_open() )
    {
      // Read each line
      while (inFile >> newRequest) {
	addToList(newRequest);
      }

      inFile.close();  // file closes 
      _nowServicing = _dailyList.begin();
    }
  else
    {
      throw std::invalid_argument( "Could not open " + filename );
    }
}

// TO DO
// the current repair has been serviced so 
// move the iterator to the next request
void RepairList::next()
{
	++_nowServicing;				//increments the list from the current repair
}


// TO DO
// add a repair request to the current list
void RepairList::addToList( const Repair& newRequest )
{
	_dailyList.push_back(newRequest);	//in the list, it will put the new repair to the back of the list
}

// TO DO
// insert a repair request coming from a loyal customer
// right after the current iterator but do not make
// changes to the current iterator
void RepairList::insertLoyal( const Repair& newRequest )
{
	std::list<Repair>::iterator current = _nowServicing; //current repair being serviced
	current++;	//increment the current service so that the loyal one can be added behind it
	_dailyList.insert(current, newRequest);	//loyal customer is inserted after the current service
}
