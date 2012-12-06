#ifndef NON_COPYABLE_HPP_INCLUDED
#define NON_COPYABLE_HPP_INCLUDED


class non_copyable
{
  protected:
    non_copyable () {}
    virtual ~non_copyable () {} /// Protected non-virtual destructor
  private:
    non_copyable (const non_copyable &);
    non_copyable & operator = (const non_copyable &);
};


#endif // NON_COPYABLE_HPP_INCLUDED
