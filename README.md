# Terrible Toys: namespace manch1n

​	As its name mentioned,actually these source codes are crazy and disaster.It just help me learned c++ language.

## mamutex.h

​	**Description**:

​		Class **`mamutex`** encasulates a pthread_mutex_t and provides lock and unlock methods.It is yet uncopyable.     

​		Class **`mamutexLockGuard`** accept a mamutex reference which helps the customer get rid of lock and forget to unlock trouble by simply usage: `mamutexLockGuard lock(mutex)`.    

## maatomic.h

​	**Description:**  

​		Class **`maatomic`** accept a arithmetic type as template parameter.Otherwise,it could not provide member functions.This class gives atomic access by using a underlying mamutex.Load() return the current value,store() sets the value and overloads ++-- operators.In addition,it provides a method to test whether current value is zero.   

## masharedptr.h

​	**Description:**  

​		After i read ***effectiveC++*** clause45,i have an inpulse to write a **`mashared_ptr`** class which supports drived class raw pointer to implictly transforms into base class mashared_ptr.  

​		I think this class has some protential risk so that I test hundreds of construct and deconstruct in multi-threads enviornment.Eventually glad that it performs right.BUT some doubts still exists:What if a shared object enter the deconstruct function but yet its reference has been minus one meanwhile other class enter the construct function and make reference add one.It's rediculous and terrible.A solution is make test zero and delete underlying data as a atomic operation but problem still exists.

## mavector.h

​	**Description:**

​		Review the basic concept of c++.

## mathreadpool.h

​	**Description:**

​		After reading the ***The C++ Standard Library*** the part of concurrency,i write a threadpool by only STL composition  including `mutex condition_variable thread`.I think it is more concise than pthread in Linux.However,Spurious wakeup in condition_variable makes me confused.