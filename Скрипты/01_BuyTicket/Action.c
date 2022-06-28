Action()
{
	lr_start_transaction("01_BuyTicket");
	
	lr_start_transaction("open_webTours");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_webTours", LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("log_in");
	
	web_reg_find("Text/IC=Welcome, <b>{login}</b>, to the Web Tours",LAST);

	web_submit_form("login.pl", 
		"Snapshot=t6.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=login.x", "Value=59", ENDITEM, 
		"Name=login.y", "Value=13", ENDITEM, 
		LAST);

	lr_end_transaction("log_in",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("click_flights");
	
	web_reg_find("Text=User has returned to the search page",LAST);

	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("click_flights",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("check_destination");

/*Correlation comment - Do not change!  Original value='241;181;06/17/2022' Name ='outboundFlight' Type ='ResponseBased'*/
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

/*Correlation comment - Do not change!  Original value='423;167;06/18/2022' Name ='returnFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=returnFlight",
		"TagName=input",
		"Extract=value",
		"Name=returnFlight",
		"Ordinal=ALL",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
		
	web_reg_find("Text/IC=Flight departing from <B>{departCity}</B> to <B>{arriveCity}</B> on <B>{departDate}</B>",LAST);
	web_reg_find("Text/IC=Flight departing from <B>{arriveCity}</B> to <B>{departCity}</B> on <B>{returnDate}</B>",LAST);

	web_submit_form("reservations.pl", 
		"Snapshot=t8.inf", 
		ITEMDATA, 
		"Name=depart", "Value={departCity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arriveCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=3", ENDITEM, 
		"Name=roundtrip", "Value=on", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=64", ENDITEM, 
		"Name=findFlights.y", "Value=4", ENDITEM, 
		LAST);
		
	lr_save_string(lr_paramarr_random("outboundFlight"),"randOutbound");
	lr_save_string(lr_paramarr_random("returnFlight"),"randReturn");

	lr_end_transaction("check_destination",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("choose_price");

	web_reg_find("Text=Payment Details",LAST);

	web_submit_form("reservations.pl_2",
		"Snapshot=t9.inf",
		ITEMDATA,
		"Name=outboundFlight", "Value={randOutbound}", ENDITEM,
		"Name=returnFlight", "Value={randReturn}", ENDITEM,
		"Name=reserveFlights.x", "Value=38", ENDITEM,
		"Name=reserveFlights.y", "Value=7", ENDITEM,
		LAST);

	lr_end_transaction("choose_price",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("details");
	
	web_reg_find("Text=Thank you for booking through Web Tours",LAST);

	web_submit_form("reservations.pl_3", 
		"Snapshot=t10.inf", 
		ITEMDATA, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM, 
		"Name=pass2", "Value={randPass}", ENDITEM, 
		"Name=pass3", "Value={randPass}", ENDITEM, 
		"Name=creditCard", "Value={creditCard}", ENDITEM, 
		"Name=expDate", "Value={expDate}", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=buyFlights.x", "Value=17", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		LAST);

	lr_end_transaction("details",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("itinerary");
	
	web_reg_find("Text=>Itinerary<",LAST);

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t7.inf", 
		LAST);

	lr_end_transaction("itinerary",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("log_out");
	
	web_reg_find("Text=Welcome to the Web Tours site",LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t11.inf", 
		LAST);

	lr_end_transaction("log_out",LR_AUTO);
	
	lr_end_transaction("01_BuyTicket", LR_AUTO);

	return 0;
}