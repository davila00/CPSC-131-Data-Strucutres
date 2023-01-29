#include <algorithm>    // find(), move(), move_backward(), equal(), swap(), lexicographical_compare()
#include <cstddef>      // size_t
#include <iomanip>      // setw()
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>

#include "BookList.hpp"

namespace   // unnamed, autonomous namespace
{
  // Avoid direct equality comparisons on floating point numbers. Two values are equal if they are "close enough", which is
  // represented by Epsilon.  Usually, this is a pretty small number, but since we are dealing with money (only two, maybe three
  // decimal places) we can be a bit more tolerant.  Two floating point values are considered equal if they are withing EPSILON of
  // each other.
  constexpr auto EPSILON = 1.0E-4;
}

/**********************************************
 **  Private implementations, types, and objects
 **  for class Book
 ************************************************/

/************************
 **  Constructor
 ************************/
Book::Book( const std::string& title,
	    const std::string& author,
	    const std::string& isbn,
	    const double & price )
  // Use the constructor initialization list
  : _isbn (isbn), _title (title), _author( author ),
    _price ( price )
{}    // Avoid setting values in constructor's body (when possible)

/*************************
 **  Queries or getters
 **************************/
std::string Book::get_isbn() const
{ return _isbn; }

std::string Book::get_title() const
{ return _title; }

std::string Book::get_author() const
{ return _author; }

double Book::get_price() const
{ return _price; }

/***********************************
 **  Mutators or setters
 ************************************/
void Book::set_isbn( const std::string& newIsbn )
{ _isbn = newIsbn; }

void Book::set_title( const std::string& newTitle )
{ _title = newTitle; }

void Book::set_author( const std::string& newAuthor )
{ _author = newAuthor; }

void Book::set_price( double newPrice )
{ _price = newPrice; }

/***********************************
 **  Friend functions: read and write
 ************************************/

std::istream & operator>>( std::istream & stream, Book & book )
{
  Book workingItem;
  
  char delimiter = ',';
  
  // Assume fields are separated by commas and string attributes are 
  // enclosed with double quotes.  For example:
  // "9789998287532", "Over in the Meadow", "Ezra Jack Keats", 91.11
  stream >> std::quoted( workingItem._isbn   ) >> delimiter
	 >> std::quoted( workingItem._title  ) >> delimiter
	 >> std::quoted( workingItem._author ) >> delimiter
	 >> workingItem._price;
  
  // If all okay, move workingItem into the returned book. Copying the 
  // information also "works" but moving is more efficient. Note this 
  // uses Book's move assignment operator.
  if(stream) book = std::move( workingItem );
  
  return stream;
}

std::ostream & operator<<( std::ostream & stream, const Book & book )
{
  const std::string delimiter = ",  ";
  stream << std::quoted( book.get_isbn()   ) << delimiter
	 << std::quoted( book.get_title()  ) << delimiter
	 << std::quoted( book.get_author() ) << delimiter
	 << book.get_price();
  
  return stream;
}


/*************************************************
 **  Ordinary functions: Relational Operators
 **************************************************/
bool operator==( const Book & lhs, const Book & rhs )
{
  // Implement equality in terms of less than to enforce identical 
  // column priority ordering and floating point epsilon comparison tolerance. 
  return lhs._isbn   == rhs._isbn
    && lhs._title  == rhs._title
    && lhs._author == rhs._author
    && std::abs( lhs._price - rhs._price ) < EPSILON;
}

bool operator!=( const Book & lhs, const Book & rhs )   
{ return !( lhs == rhs ); }

/**********************************************
 **  Private implementations, types, and objects
 ** for class BookList
 ************************************************/

/*************************************
 **  Friend functions: read and write
 **************************************/

std::ostream & operator<<( std::ostream & stream, const BookList & bookList )
{
  
  for (unsigned i=0; i< bookList._books_array_size; i++) {
    stream << '\n' << std::setw(5) << i << ":  " << bookList[i];
  }
  return stream;
}


std::istream & operator>>( std::istream & stream, BookList & bookList )
// read at most <_capacity> books
{
  Book book;
  unsigned counter = 0;
  
  while(stream && counter < bookList._capacity) {
    stream >> book;
    bookList._bookArray[counter++] = std::move(book);
  }
  
  if (counter < bookList._capacity)
    // read less books than <_capacity>
    // so set it to actual number of books read
    bookList._books_array_size = counter;
  
  return stream;
}

/***********************
 ** Constructor
 ************************/
// TO DO
BookList::BookList(const std::size_t & newSize)
{ 
    _bookArray = new Book[newSize];                     //A new book will add to the total and subsequently add to the total array while also adding to the capacity (30 max)
    _books_array_size = 0;                                //By default it will be 0, unless otherwise stated
    _capacity = newSize;                                  //Will be called with the number of books total so it will also be the capacity
}

/************************
 ** Assignment operator
 ************************/
// TO DO
BookList & BookList::operator+=( const BookList & rhs)
  // Concatenate the righthand side book list of books to this list 
  // by repeatedly adding each book at the end of the current book list 
  // as long as it does not exceed <_capacity>
  // If exceeds, then stop adding
      //while
{//issue here
    int rhsBookList = 0;                                                            //To count the number of iterations
    while (_books_array_size < _capacity && rhsBookList < rhs.size())         //Keeps iterating while the number of books is less than the max number of books && if the rhs is less than the size of the book array
    {
        _bookArray[_books_array_size++] = rhs[rhsBookList++];                 //In order for it to keep traversing through the array, it needs to be incremented within the array index 
    }                                                                                 //# of books will grow as long as it is equal to the righthand in terms of iterations, lhs is equal to rhs
    return (*this);                                                                  //All assignment operators retun (*this)
}

/*********************
 ** Destructor
 *********************/
// TO DO 
BookList::~BookList()
{
    _capacity = 0;                                          //Deletes the capacity of the array
    _books_array_size = 0;                               //Deletes the size of the array
    delete []_bookArray;                                  //Deletes the allocated memory from the array
}

/***********************
 ** Queries or getters
 ************************/
// TO DO
std::size_t BookList::size() const
{
  // return the size of the dynamic array
    return _books_array_size;                           //Returns the number of books in the list
}

//TO DO
std::size_t BookList::find( const Book & book ) const
// Locate the book in this book list and return the zero-based position 
// of that book. If the book does not exist, return the size of this 
// book list as an indicator the book does not exist.
    //for
{
    for (unsigned i = 0; i < _books_array_size; i++)    //for loop of size_t since the query is of size_t and it will go through list to return the position of the current book
    {
        if (_bookArray[i] == book)
        {
            return i;                                       //Returns the current position of that book from the for loop's iteration counter, if the specific book IS found
        }
    }
    return _books_array_size;                           //Returns the size of this book list, if the specific IS NOT found
}

Book BookList::operator[](std::size_t index) const 
{
  return _bookArray[index];                             //Returns the book at the index specified 
}

/*************************
 ** Read from the file
 **************************/
void BookList::readInFile(const std::string& filename) {
  std::ifstream inFile(filename);
  Book newBook;
  unsigned i=0;
  
  // Read each line
  while ((inFile >> newBook) && (i < _capacity)) {
    _bookArray[i++] = newBook;
  }
  
  _books_array_size = i;
}
