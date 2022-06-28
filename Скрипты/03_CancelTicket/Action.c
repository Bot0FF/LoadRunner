Action()
{	
	int i;
	int randNum;
	
	lr_start_transaction("03_Cancel_Ticket");

	lr_start_transaction("open_webTours");

/*Correlation comment - Do not change!  Original value='134081.454515998ziQziVtpiVzzzzzHtVDiApiiiQ' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);
			
	web_reg_find("Text=Welcome to the Web Tours site",LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_webTours", LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("log_in");

/*Correlation comment - Do not change!  Original value='itinerary' Name ='page' Type ='ResponseBased'*/
	web_reg_save_param_regexp(
		"ParamName=page",
		"RegExp=page=(.*?)\"\\ TARGET",
		"Ordinal=2",
		SEARCH_FILTERS,
		"Scope=Body",
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);
				
	web_reg_find("Text=User password was correct",LAST);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=login.x", "Value=51", ENDITEM,
		"Name=login.y", "Value=9", ENDITEM,
		LAST);

	lr_end_transaction("log_in",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("itinerary");
	
	web_reg_save_param("c_flightids",
    "lb=<input type=\"hidden\" name=\"flightID\" value=\"",
    "rb=\"  />",
    "ord=all",
    LAST);
		
	web_reg_find("Text=A total of",LAST);

	web_url("Itinerary Button",
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page={page}",
		"TargetFrame=body",
		"Resource=0",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home",
		"Snapshot=t3.inf",
		"Mode=HTML",
		LAST);

	lr_end_transaction("itinerary",LR_AUTO);
	lr_think_time(5);
	
	//find random number from all tickets
	randNum = rand()%atoi(lr_eval_string("{c_flightids_count}")) + 1;
	lr_save_int(randNum, "randNum");
	
	//save cancel ticket id
	lr_save_string(lr_paramarr_idx("c_flightids", randNum), "cancel_ticket_id");
	
	lr_start_transaction("cancel_ticket");
  
	web_submit_form("itinerary.pl", 
		"Snapshot=t13.inf", 
		ITEMDATA, 
		"Name={randNum}", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=40", ENDITEM, 
		"Name=removeFlights.y", "Value=13", ENDITEM, 
		LAST);

	lr_end_transaction("cancel_ticket",LR_AUTO);
	lr_think_time(5);
	
	if(atoi(lr_eval_string("{random}")) == 1)		
	{ 
	lr_start_transaction("itinerary");
			
	web_reg_find("Text={cancel_ticket_id}", "Fail=Found", LAST);

		web_url("Itinerary Button",
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page={page}",
		"TargetFrame=body",
		"Resource=0",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home",
		"Snapshot=t3.inf",
		"Mode=HTML",
		LAST);

	lr_end_transaction("itinerary",LR_AUTO);
	lr_think_time(5);
	}
	
	if(atoi(lr_eval_string("{random}")) == 1)	
	{ 	
	lr_start_transaction("log_out");
	
	web_reg_find("Text=Web Tours", LAST);

	web_url("SignOff Button",
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1",
		"TargetFrame=body",
		"Resource=1",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in={page}",
		"Snapshot=t5.inf",
		"Mode=HTML",
		LAST);

	lr_end_transaction("log_out",LR_AUTO);
	}
	
	lr_end_transaction("03_Cancel_Ticket", LR_AUTO);

	return 0;
}