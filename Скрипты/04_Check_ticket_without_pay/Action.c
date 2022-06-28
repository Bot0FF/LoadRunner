Action()
{
	lr_start_transaction("04_Check_ticket_without_pay");
	
	lr_start_transaction("open_webTours");
	
	web_reg_find("Text=Welcome to the Web Tours",LAST);

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
		"Name=login.x", "Value=46", ENDITEM, 
		"Name=login.y", "Value=8", ENDITEM, 
		LAST);

	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_end_transaction("log_in",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("click_flights");
	
	web_reg_find("Text=User has returned to the search page",LAST);

/*Correlation comment - Do not change!  Original value='06/24/2022' Name ='returnDate' Type ='RecordReplay'*/
	web_reg_save_param_attrib(
		"ParamName=returnDate",
		"TagName=input",
		"Extract=value",
		"Name=returnDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);

/*Correlation comment - Do not change!  Original value='06/23/2022' Name ='departDate' Type ='RecordReplay'*/
	web_reg_save_param_attrib(
		"ParamName=departDate",
		"TagName=input",
		"Extract=value",
		"Name=departDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("click_flights",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("check_destination");

/*Correlation comment - Do not change!  Original value='352;271;06/23/2022' Name ='outboundFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Ordinal=ALL",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
		
		web_reg_find("Text/IC=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate}</B>",LAST);

	web_submit_form("reservations.pl",
		"Snapshot=t4.inf",
		ITEMDATA,
		"Name=depart", "Value={departCity}", ENDITEM,
		"Name=departDate", "Value={departDate}", ENDITEM,
		"Name=arrive", "Value={arriveCity}", ENDITEM,
		"Name=returnDate", "Value={returnDate}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=roundtrip", "Value=<OFF>", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=findFlights.x", "Value=54", ENDITEM,
		"Name=findFlights.y", "Value=10", ENDITEM,
		LAST);
		
	lr_save_string(lr_paramarr_random("outboundFlight"),"randOutbound");

	lr_end_transaction("check_destination",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("choose_price");
	
	web_reg_find("Text=Payment Details",LAST);

	web_submit_form("reservations.pl_2",
		"Snapshot=t5.inf",
		ITEMDATA,
		"Name=outboundFlight", "Value={randOutbound}", ENDITEM,
		"Name=reserveFlights.x", "Value=33", ENDITEM,
		"Name=reserveFlights.y", "Value=3", ENDITEM,
		LAST);

	lr_end_transaction("choose_price",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("log_out");
	
	web_reg_find("Text=Welcome to the Web Tours",LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t6.inf", 
		LAST);

	lr_end_transaction("log_out",LR_AUTO);
	
	lr_end_transaction("04_Check_ticket_without_pay", LR_AUTO);

	return 0;
}