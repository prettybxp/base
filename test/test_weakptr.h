#pragma once

#include "base/memory/weak_ptr.h"
#include "base/threading/thread_task_runner_handle.h"

class Person : public base::RefCounted<Person>
{
public:
    Person(std::string const& name):name_(name),weak_factory_(this)
    {
        LOG(INFO) << "Person "<<name_<<" Create";
    }
    ~Person()
    {
        LOG(INFO) << "Person "<<name_<<" Delete";
    }

    void SayHello1(int age)
    {
        scoped_refptr<base::SingleThreadTaskRunner> task_runner = base::ThreadTaskRunnerHandle::Get();
	    task_runner->PostTask(FROM_HERE, base::BindOnce(&Person::Hello, this, age));
    }

    void SayHello2(int age)
    {
        scoped_refptr<base::SingleThreadTaskRunner> task_runner = base::ThreadTaskRunnerHandle::Get();
	    task_runner->PostTask(FROM_HERE, base::BindOnce(&Person::Hello, weak_factory_.GetWeakPtr(), age));
    }

    void Hello(int age)
    {
        LOG(INFO) << "Hello, my name is " << name_ << ", I am " << age << " years old";
    }

private:
    std::string name_;
    base::WeakPtrFactory<Person> weak_factory_;
};


void TestWeakPtr()
{
    {
        scoped_refptr<Person> person = new Person("Tom");
        person->SayHello1(20);
    }

    {
        scoped_refptr<Person> person = new Person("Bob");
        person->SayHello2(25);
    }
}
