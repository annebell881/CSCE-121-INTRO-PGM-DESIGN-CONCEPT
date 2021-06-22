#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

bool is_negitive(string str){
	//if num is negitive erases the negitive value and sets bool to true
	if (str.find('-') != std::string::npos){
		return true;
	}
	return false;
}

unsigned int digit_to_decimal(char digit) {
    //creates an int
	unsigned int digit_to_deci = 0;
	//converts the char to a number that corresponds with the number
	if (digit == '0'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '1'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '2'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '3'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '4'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '5'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '6'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '7'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '8'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	else if (digit == '9'){
		digit_to_deci = digit - '0';
		return digit_to_deci;
	}
	//otherwise throws invaild arugment
	else{
		throw std::invalid_argument(" ");
	}
		
	
}

char decimal_to_digit(unsigned int decimal) {
    //creates a char
	char deci_to_digit = ' ';
	//assigns the int to corresponding char
	if (decimal == 0){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 1){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 2){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 3){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 4){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 5){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 6){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 7){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 8){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	else if (decimal == 9){
		deci_to_digit = decimal + '0';
		return deci_to_digit;
	}
	//else throws an invaild arugment
    else{
		throw std::invalid_argument(" ");
	}
}

string trim_leading_zeros(string num) {
    //creates a bool for testing if a num is negitive
	bool is_negitive = false;
	//if num is negitive erases the negitive value and sets bool to true
	if (num.find('-') != std::string::npos){
		is_negitive = true;
		num.erase(0,1);
	}
	//trims the leading zeros of the string
	num.erase(0, num.find_first_not_of('0'));
	//if the num was negitive returns the negitive sign to the front
	if(is_negitive && !(num.find_first_not_of('0') == std::string::npos)){
		num.insert(0, 1,'-');	
	}
	// creates a case if the number is infact equal to zeros
	if(num.find_first_not_of('0') == std::string::npos){
		string zero_string = "0";
		return zero_string;
	}
	//returns the string
    return num;
}

string add(string lhs, string rhs) {
	//define if negitive and return string without -
	bool string1 = is_negitive(lhs);
	bool string2 = is_negitive(rhs);
	
	if (string1){
		lhs.erase(0,1);
	}
		
	if (string2){
		rhs.erase(0,1);
	}
	
	// define both strings sizes
	unsigned string1_size = lhs.size();
	unsigned string2_size = rhs.size();
	
	//define temp strings
	string temp_largest;
	string temp_smallest;
	
	//find out which string is the largest
	if(string1_size > string2_size){
		temp_largest = lhs;
		temp_smallest = rhs;
	}
	else if (string1_size < string2_size){
		temp_largest = rhs;
		temp_smallest = lhs;
	}
	else{
		temp_largest = rhs;
		temp_smallest = lhs;
	}
	
	//create a new variables to store the answer
	string answer_string;
	int carry = 0;
	unsigned l_size = temp_largest.size();
	unsigned s_size = temp_smallest.size();
	unsigned n1 = l_size -1;
	unsigned n2 =s_size-1;
	//reverse the two strings
	for(unsigned i = 0; i < (l_size/2); i++){
		std::swap(temp_largest.at(i),temp_largest.at(n1));
		n1 -= 1;
	}
	for(unsigned i = 0; i < (s_size/2); i++){
		std::swap(temp_smallest.at(i),temp_smallest.at(n2));
		n2 -= 1;
	}
	
	// add 
	for (unsigned i = 0; i < s_size; i++){
		unsigned sum = (digit_to_decimal(temp_smallest.at(i)) + digit_to_decimal(temp_largest.at(i)) + carry);
		answer_string.push_back(decimal_to_digit((sum%10)));
		carry = sum / 10;
	}
	for (unsigned i = s_size; i < l_size; i++){
		unsigned sum = (digit_to_decimal(temp_largest.at(i)) + carry);
		answer_string.push_back(decimal_to_digit((sum%10)));
		carry = sum / 10;
	}
	if (carry != 0){
		answer_string.push_back(decimal_to_digit(carry));
	}
	
	unsigned answer_size = answer_string.size();
	unsigned n3 = answer_size - 1;
	
	//reverse string back
	for(unsigned i = 0; i < (answer_size/2); i++){
		std::swap(answer_string.at(i),answer_string.at(n3));
		n3 -= 1;
	}
	
	if((string1 && string2) || (string1 && rhs == "0" ) || (string2 && lhs == "0")){
		answer_string.insert(0,1,'-');
	}
    
    return answer_string;
}

/*string compliment(string tenComp){
	//create a new string
	string helper = "";
	int c = 0;
	//subtract every number in tenComp with 9
	for(unsigned i = 0; i < tenComp.size()- 1; i++){
		c = 9 - digit_to_decimal(tenComp.at(i));
		helper += decimal_to_digit(c);
	}

	// add one to helper
	helper = add(helper, "1" );
	
	return helper;
}*/
   
string subtract(string lhs, string rhs) {
	bool string1 = is_negitive(lhs);
	bool string2 = is_negitive(rhs);
	
	if (string1){
		lhs.erase(0,1);
	}
		
	if (string2){
		rhs.erase(0,1);
	}
	
	string temp_largest;
	string temp_smallest;
	unsigned string1_size = lhs.size();
	unsigned string2_size = rhs.size();
	//find out which string is the largest
	if(string1_size > string2_size){
		temp_largest = lhs;
		temp_smallest = rhs;
	}
	else if (string1_size < string2_size){
		temp_largest = rhs;
		temp_smallest = lhs;
	}
	else{
		temp_largest = rhs;
		temp_smallest = lhs;
	}
	
	//create a new variables to store the answer
	string answer_string;
	int carry = 0;
	unsigned l_size = temp_largest.size();
	unsigned s_size = temp_smallest.size();
	unsigned n1 = l_size - 1;
	unsigned n2 = s_size - 1;
	//reverse the two strings
	for(unsigned i = 0; i < (l_size/2); i++){
		std::swap(temp_largest.at(i),temp_largest.at(n1));
		n1 -= 1;
	}
	for(unsigned i = 0; i < (s_size/2); i++){
		std::swap(temp_smallest.at(i),temp_smallest.at(n2));
		n2 -= 1;
	}
	//subtract
	for (unsigned i = 0; i < s_size; i++){
		int sub = (digit_to_decimal(temp_smallest.at(i)) - digit_to_decimal(temp_largest.at(i)) - carry);
		if (sub < 0){
			sub = sub + 10;
			carry = 1;
		}
		else{
			carry = 0;
		}
		answer_string.push_back(decimal_to_digit(sub));
	}
	for (unsigned i = s_size; i < l_size; i++){
		int sub  = (digit_to_decimal(temp_largest.at(i)) - carry);
		if(sub < 0){
			sub += 10;
			carry = 1;
		}
		else{
			carry =0;
		}
		
		answer_string.push_back(decimal_to_digit((sub)));
		
	}
	if (carry != 0){
		answer_string.push_back(decimal_to_digit(carry));
	}
	
	unsigned answer_size = answer_string.size();
	unsigned n3 = answer_size - 1;
	
	//reverse string back
	for(unsigned i = 0; i < (answer_size/2); i++){
		std::swap(answer_string.at(i),answer_string.at(n3));
		n3 -= 1;
	}
	
	
	
	return answer_string;
	
}



string multiply(string lhs, string rhs) {		
	bool string1 = is_negitive(lhs);
	bool string2 = is_negitive(rhs);
	
	if (string1){
		lhs.erase(0,1);
	}
		
	if (string2){
		rhs.erase(0,1);
	}
	// define both strings sizes
	unsigned string1_size = lhs.size();
	unsigned string2_size = rhs.size();
	// create a new string to hold our answer
	string answer_string = "";
	
	if (string1_size == 1 && string2_size == 1){
		int product = digit_to_decimal(lhs.at(1)) * digit_to_decimal(lhs.at(1));
		answer_string.push_back(decimal_to_digit(product));
		
		if(string1 || string2){
			answer_string.insert(0,1,'-');
		}
		
		return answer_string;
	}
		
	

	//try to do this like on paper
	for(unsigned i = string2_size; i > 0; i--){
		int carry = 0;
		string temp = "";
		// should get first num to mutiply and so on
		unsigned num1 = decimal_to_digit(rhs.at(i));
		// shift to the second string
		
		for (unsigned j = string1_size; j > 0; j--){
			unsigned num2 = decimal_to_digit(lhs.at(j));
			int productN = num1 * num2 + carry;
			carry = productN / 10;
			temp.push_back(digit_to_decimal(productN));
		}
		
		if (carry > 0){
			temp.push_back(digit_to_decimal(carry));
		}
		
		if (i == string2_size - 1){
			answer_string = temp;
		}
		else{
			add(answer_string, temp);
		}
	}
		
    
    return answer_string;
	
}
