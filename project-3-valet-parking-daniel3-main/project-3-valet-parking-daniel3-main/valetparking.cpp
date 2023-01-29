#include "valetparking.hpp"

// ATTENTION STUDENTS:
// THE CONSTRUCTORS ARE ALREADY COMPLETED.
// YOU NEED TO COMPLETE THE DESTRUCTOR AND ALL OF THE REMAINING FUNCTIONS BELOW.

// CONSTRUCTORS - ALREADY COMPLETE
ValetParking::ValetParking() : _numberofstalls(1), _stallcapacity(1), _queuecapacity(1), _currentticket(0),
_fee(5.0), _paid(0.0), _checkout(new std::queue<size_t>()), _parkingstall(_numberofstalls, std::stack<size_t>())
{}

ValetParking::ValetParking(size_t numberofstalls, size_t stallcapacity,
    size_t queuecapacity, size_t ticketnumber, double fee) : _numberofstalls(numberofstalls), _stallcapacity(stallcapacity), _queuecapacity(queuecapacity), _currentticket(ticketnumber),
    _fee(fee), _checkout(new std::queue<size_t>()), _parkingstall(_numberofstalls, std::stack<size_t>()), _paid(0.0)
{}

// DESTRUCTOR
ValetParking::~ValetParking() = default;

size_t ValetParking::totalStallSpaces()
// return the maximum number of cars that all stalls can accommodate
{
    return (_numberofstalls * _stallcapacity); //multiply the number of stalls to the number of spaces in the stalls for total spaces
}

size_t ValetParking::carsInStalls()
// return the number of cars parked in all the stalls
{
    size_t carsStalls = 0;
    for (auto i = 0; i < _numberofstalls; i++) //loop that iterates through the stalls and counts the cars in each
    {
        carsStalls = carsStalls + _parkingstall[i].size(); //each car in each space gets added to the counter
    }
    return carsStalls; //number of total cars
}

size_t ValetParking::carsInCheckOut()
// return the number of cars waiting in checkout line to pay before exiting the lot.
{
    return _checkout->size(); //the checkout queue size is returned
}

size_t ValetParking::availableStallSpaces()
// return the number of available parking spaces in all the stalls
{
    auto spacesAvailable = 0;
    if (!stallEmpty())
    {
        return spacesAvailable = totalStallSpaces() - carsInStalls();
    }
    else
    {
        return totalStallSpaces();
    }
}

double ValetParking::totalSales()
// return the total amount based on the number of tickets issued
{
    return (_currentticket * _fee); //the tickets issued is multiplied to the fee so that a total price is reached
}

size_t ValetParking::pay()
// remove and return the ticket# of car at front of the checkout queue, and the fee is collected.
{
    size_t ticketNumber = 0;
    if (_checkout->empty()) //if the queue is empty then there is no action(value to pay)
    {
        return 0;
    }
    else
    {
        _paid = _paid + _fee; //the fee is added to the amount paid in total by number of tickets issued
        ticketNumber = _checkout->front(); //the front ticket is used to pay
        _checkout->pop(); //front ticket is them removed to move onto the next
        return ticketNumber; //ticket paid for
    }
}

double ValetParking::totalPaid()
// return the total amount customers have paid so far based on the number of cars exited the lot.
{
    return _paid; //total paid amount
}

bool ValetParking::parkingEmpty()
// return true if all stalls and checkout queue are empty
{
    if (queueEmpty() && stallEmpty()) //if stalls are empty and queue is empty
    {
        return true; //then the lot is empty
    }
}

bool ValetParking::parkingFull()
// return true if all stalls and checkout queue are full
{
    if (queueFull() && stallFull()) //if stalls and queue are full
    {
        return true; //then the lot is full
    }
}

bool ValetParking::queueEmpty()
// return true if the checkout queue is empty
{
    if (_checkout->size() == _checkout->empty()) //if the queue size is the same as the queue empty
    {
        return true; //then the queue is empty
    }
}

bool ValetParking::queueFull()
// return true if the checkout queue is full
{
    if (_checkout->size() == _queuecapacity) //if the queue size is the same as its capacity
    {
        return true; //then the queue is full
    }
}

bool ValetParking::stallEmpty()
// return true if all stalls are empty
{
    for (auto i = 0; i < _parkingstall.size(); i++) //for-loop to iterate through the size of parkingstall
    {
        if (!_parkingstall[i].empty()) //if the space is  not empty from stall
        {
            return false; //then return false
        }
    }
    return true; //else return true
}

bool ValetParking::stallFull()
// return true if all stalls are full
{
    for (auto i = 0; i < _parkingstall.size(); i++) //loop that iterates through the the stall size
    {
        if (_parkingstall[i].size() != _numberofstalls * _stallcapacity) //if the space is not taken by a car
        {
            return false; //then there is an empty space so it returns false
        }
    }
    return true; //if the spot is full then it returns true
}

size_t ValetParking::getNextTicket()
// return the next ticket number to issue to customer
{
    return ++_currentticket; //next ticket to be issued
}

size_t ValetParking::checkIn()
// on success return stall# (index-1 base), on failure return 0.
{
    for (auto i = 0; i < _parkingstall.size(); ++i) // for loop that iterates to through the size of stalls
    {
        if (_parkingstall[i].size() != _stallcapacity) //if the space does not equal to the capacity
        {
            _parkingstall[i].push(getNextTicket()); //then the ticket will get the next ticket from the space
            return i + 1; //return + 1 space
        }
    }
    return 0; //else return 0
}

size_t ValetParking::stallNumber(size_t ticket)
// return the stall number (index-1 base) in which the ticket number resides
{
    if (!_parkingstall[(ticket / _stallcapacity) - 1].empty()) //if ticket does not  exist in the function
    {
        auto stallTicketNumber =_parkingstall[(ticket / _stallcapacity) - 1].top(); //variable which keeps holds the the ticket
        if (ticket > stallTicketNumber) //then if the ticket is passed the one being searched for
        {
            return (ticket / _stallcapacity) + 1 ; //then return the ticket from capacity added to 1
        }
    }
    return (ticket / _stallcapacity); //return the ticket from capacity
}

bool ValetParking::checkOut(size_t stallnumber, size_t ticket)
// Retrieve the ticket# from the stall and place the ticket in the checkout queue.
// On success return true.
{
    if (stallEmpty()) //if the stalls are empty
    {
        return false; //then there is no one to check out and it is empty so it is false
    }
    else
    {
        //throw std::range_error("ERROR: checkOut else");
        _checkout->push(ticket); //push the ticket to the checkout queue 
        _parkingstall[stallnumber - 1]; //once the ticket is pushed it goes to next space to checkout 
        return true; //returns true since there is an occupied space
    }
}