#include <bitset>
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

struct type{
	int n;
	type( int _n ) { n = _n; }
};

bool isvalid(type & a) {
	return a.n>0;
}

int main()
{
	int a,b, arr[10], N=10, M=20;

	//BITSET

	bitset<MAXN> bit;	//MAXN = size
	bit.reset();	// set all bits to 0
	bit.size();		//return size
	bit.set(a,b);	//set bit a (0 indexed) to b (0 or 1)
	bit.flip(a);	//flips bit a
	bit.count();	//return number os 1's
	bit.any();		//test if any bit is set
	bit.none();		//Test if no bit is set
	bit.all();		//Test if all bits are set
	bit.to_string();//converts to std::string
	bit.to_ulong();	//converts to long int
	bit.to_ullong();//converts to long long int

	//VECTOR

	vector<type> vet;
	vector<type>::iterator vit;
	vet.begin();	//Return iterator to beginning
		vit = vet.begin();	//*vit = vet[0];
		vet.cbegin();	//Return const_iterator to beginning
	vet.end();		//Return iterator to end
		vit = vet.end();	//*vit = vet[size];
		vet.cend();		//Return const_iterator to end
	vet.rbegin();	//Return reverse iterator to reverse beginning
		vit = vet.rbegin();	//*vit = vet[size-1];
		vet.crbegin();	//Return const_reverse_iterator to reverse beginning
	vet.rend();		//Return reverse iterator to reverse end
		vit = vet.rend();	//*vit = vet[-1];
		vet.crend();	//Return const_reverse_iterator to reverse end
	vet.size();		//Return size
	vet.max_size();	//Return maximum size
		a = vet.max_size();	//maximum number of size for given machine
	vet.resize();	//Change size
		vet.clear();
		vet.resize(5);		//0 0 0 0 0
  		vet.resize(8,100);	//0 0 0 0 0 100 100 100
  		vet.resize(12)		//0 0 0 0 0 100 100 100 0 0 0 0
	vet.capacity();	//Return size of allocated storage capacity
	vet.empty();	//Test whether vector is empty
	vet.reserve(N);	//Request a change in capacity
		vet = std::vector<type>(100);	//vet.capacity() = 100
		vet.reserve(200);				//vet.capacity() = 200
	vet.shrink_to_fit();//Shrink to fit
		vet = std::vector<type>(100);	//vet.capacity() = 100
		vet.resize(10);					//vet.capacity() = 100
		vet.shrink_to_fit();			//vet.capacity() = 10
	vet.front();	//Access first element (vet[0])
	vet.back();		//Access last element (vet[size-1])
	vet.data();		//Access data (&vet[0])
	vet.assign(a,b);	//Assign vector content (a types with value b)
	vet.push_back(a);	//Add element at the end (vet[size++]=a)
	vet.pop_back();		//Delete last element (size--)
	vet.insert(vit, a);		//Insert elements
		vet.insert(vit, a)		//insert element a at position (vit-vet.begin())
		vet.insert(vit, arr, arr+N);	//insert first N elements of array arr at position (vit-vet.begin())
	vet.erase();		//Erase elements
		vet.erase(vet.begin() + N);	//erase Nth element
		vet.erase(vet.gebin() + N, vet.begin() + M);	//erase Nth element to M-1th element
	vet.swap();			//Swap content
		vet1.swap(vet2);	//swap(vet1, vet2), O(1)
	vet.clear();		//Clear content


	//ALGORITHM

	sort(vet.begin(), vet.end());	//sort std::vector, O(nlogn)
		sort(vet.begin(), vet.end(), &comp);	//custom compare function (less than)
		sort(arr, arr+N);			//sort array, O(nlogn)
		sort(arr, arr + N, &comp);	//custom compare function (less than)
	next_permutation(vet.begin(), vet.end());	//next lexicographic permutation of std::vector, O(n)
		next_permutation(vet.begin(), vet.end(), &comp);	//custom compare function (less than)
		next_permutation(arr, arr+N);			//next lexicographic permutation of array, O(n)
		next_permutation(arr, arr + N, &comp);	//custom compare function (less than)
	nth_element(vet.begin(), vet.begin()+N, v.end());	//puts nth element in place std::vector those less than
														//it are put in random order before N, same for those greater, O(n)
		nth_element(vet.begin(), vet.begin()+N, v.end(), &comp);	//custom compare function (less than)
		nth_element(arr, arr+N, arr+M);			//nth_element for array
		nth_element(arr, arr+N, arr+M, &comp);	//custom compare function (less than)

	//LIST

	list<type> l, l1, l2;
	list<type>::iterator lit;
	l.begin();	//Return iterator to beginning
		lit = l.begin();	//*vit = vet[0];
		l.cbegin();	//Return const_iterator to beginning
	l.end();		//Return iterator to end
		lit = l.end();	//*vit = vet[size];
		l.cend();		//Return const_iterator to end
	l.rbegin();	//Return reverse iterator to reverse beginning
		lit = l.rbegin();	//*vit = vet[size-1];
		l.crbegin();	//Return const_reverse_iterator to reverse beginning
	l.rend();		//Return reverse iterator to reverse end
		lit = l.rend();	//*vit = vet[-1];
		l.crend();	//Return const_reverse_iterator to reverse end
	l.size();		//Return size
	l.max_size();	//Return maximum size
	l.assign();		//Assign new content to container
	l.push_front(type(a));		//Insert element at beginning
	l.pop_front();	//Delete first element
	l.push_back(type(a));		//Add element at the end
	l.pop_back();		//Delete last element
	l.insert(lit, type(a));		//Insert elements before lit
	l.erase(lit);		//Erase elements, lit receives next
	l1.swap(l2);		//Swap content of list l1 and l2, O(1)
	l.resize(a);		//Change size, adds zeros, O(n)
	l.clear();			//Clear list
	l1.splice(lit, l2);	//Transfer elements from list l2 to list l1 behind lit, O(n)
	l.remove(type(b));	//Remove elements with value type(b), O(n)
	l.remove_if(&isvalid);	//Remove elements fulfilling condition (function isvalid(n))
	l.unique();			//Remove duplicate values
	l1.merge(l2, &comp);//Merge sorted lists
	l.sort();			//Sort elements in container O(nlogn)
		l.sort(&comp);	//Sort according to comp(n,m)
	l.reverse();		//Reverse the order of elements

	//STACK

	stack<type> s, s1, s2;
	s.empty();		//Test whether container is empty
	s.size();		//Return size
	s.top();		//Access next element
	s.push(type(a));		//Insert element
	s.pop();		//Remove top element
	s1.swap(s2);	//Swap contents
}