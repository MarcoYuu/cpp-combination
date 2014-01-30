
#ifndef COMBINATION_H_
#define COMBINATION_H_

#include <vector>

class combination{
	std::vector<int> prev_;
	std::vector<int> flag_;
	int set_;
	int choice_;
	int count_;
	int combo_;

public:
	combination(int set, int choice);

	void reset(int set, int choice);

	inline bool is_end() const;
	inline int combinations() const;

	void next(std::vector<int> &result);
	const std::vector<int>& next();

	inline const std::vector<int>& operator ++();
	inline const std::vector<int> operator ++(int);
	inline const std::vector<int>& operator *();
	inline const int operator [](int index);
};


inline bool combination::is_end() const{
	return count_ > combo_ ? true : false;
}

inline int combination::combinations() const{
	return combo_;
}

inline const std::vector<int>& combination::operator ++(){
	return next();
}

inline const std::vector<int> combination::operator ++(int){
	std::vector<int> tmp = prev_;
	next();
	return tmp;
}

inline const std::vector<int>& combination::operator *(){
	return prev_;
}

inline const int combination::operator [](int index){
	return prev_[index];
}

#endif
