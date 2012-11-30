#ifndef COUPLE_H
#define COUPLE_H

class Couple
{
	private :
		int _id;
		int _deg;
		
	public :
		Couple(const int &, const int &);
		
		int id() const;
		int deg() const;
		
		void min();
		void min(const int&);
		void add();
		
		Couple operator < (const Couple &);
};

#endif
