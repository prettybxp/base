#pragma once


#include "base/bind.h"


void TestCallback()
{
	base::Callback<int(int, int)> add = base::Bind([](int a, int b){
		return a + b;
	});

	LOG(INFO)<<"1+2="<<add.Run(1, 2);
	LOG(INFO)<<"3+5="<<add.Run(3, 5);

	base::OnceCallback<int(int, int)> del = base::Bind([](int a, int b){
		return a - b;
	});

	//LOG(INFO)<<"4-3="<<del.Run(4, 3);   //wrong
	LOG(INFO)<<"5-3="<<std::move(del).Run(5, 3);  
	//LOG(INFO)<<"4-2="<<std::move(del).Run(4, 2);  //wrong
}