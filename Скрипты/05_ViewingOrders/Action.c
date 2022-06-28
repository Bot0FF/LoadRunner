Action()
{
	lr_start_transaction("05_ViewingOrders");

	lr_start_transaction("open_webTours");
	
	web_reg_find("Text=Welcome to the Web Tours site",LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_webTours", LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("log_in");
	
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours",LAST);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=login.x", "Value=52", ENDITEM, 
		"Name=login.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("log_in",LR_AUTO);
	lr_think_time(5);
	
	
	if(atoi(lr_eval_string("{random}")) == 0)
		
	{       

	lr_start_transaction("click_flights");

		web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("click_flights",LR_AUTO);
	lr_think_time(5);

	}
	
	lr_end_transaction("05_ViewingOrders", LR_AUTO);

	return 0;
}