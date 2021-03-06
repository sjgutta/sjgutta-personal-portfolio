#include "company.hpp"
#include <vector>

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  // your implementation goes here
  //delete all in parents vector
  for(int i=0; i<int(parents.size()); i++){
    if(parents[i]!=nullptr){
      delete parents[i];
    }
  }
  //deleting child companies
  for(int i=0; i<numCompanies; i++){
    delete companies[i];
  }
  //deleting the companies array
  delete [] companies;
}

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  // your implementation goes here
  //check for out of bounds or equal
  if(i<0||i>=numCompanies){
    return;
  }
  if(j<0||j>=numCompanies){
    return;
  }
  if(i==j){
    return;
  }
  //find companies to merge
  Company* company1 = findLargestCompany(i);
  Company* company2 = findLargestCompany(j);
  if(company1==company2){
    return;
  }
  //create new company to be parent
  Company* new_parent = new Company(company1,company2);
  //set merged companies to have this parent company
  company1->parent=new_parent;
  company2->parent=new_parent;
  parents.push_back(new_parent);
}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  // your implementation goes here
  if(i<0||i>=numCompanies){
    return;
  }
  //find largest company to be split
  Company* largest = findLargestCompany(i);
  if(largest->merge1==nullptr){
    return;
  }
  //setting merged companies to have no parent
  largest->merge1->parent=nullptr;
  largest->merge2->parent=nullptr;
  //deleting the parent company from the vector of parents
  for(int i=0; i<int(parents.size()); i++){
    if(parents[i]==largest){
      delete parents[i];
      parents.erase(parents.begin()+i);
      return;
    }
  }
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  // your implementation goes here
  if(i<0||i>=numCompanies){
    return false;
  }
  if(j<0||j>=numCompanies){
    return false;
  }
  //checking cases to see if same company
  if(i==j){
    return true;
  }else if(findLargestCompany(i)==findLargestCompany(j) && companies[i]->parent){
    return true;
  }else{
    return false;
  }
}

Company* CompanyTracker::findLargestCompany(int i){
  //finding top most parent for this company
  Company* result = companies[i];
  while(result->parent){
    result = result->parent;
  }
  return result;
}
