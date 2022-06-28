Action()
{
	
	RndStr("rndStr",7);
	
	lr_start_transaction("02_RegistrationWebTours");
	
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
	lr_start_transaction("sing_up");

	web_reg_find("Text=First time registering?",LAST);

	web_link("sign up now", 
		"Text=sign up now", 
		"Snapshot=t2.inf", 
		LAST);
		
	web_set_sockets_option("SSL_VERSION", "AUTO");

	lr_end_transaction("sing_up",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("customer_profile");

	web_reg_find("Text=Thank you, <b>{rndStr}</b>, for registering", LAST);

	web_submit_form("login.pl", 
		"Snapshot=t3.inf", 
		ITEMDATA, 
		"Name=username", "Value={rndStr}", ENDITEM, 
		"Name=password", "Value={rndStr}", ENDITEM, 
		"Name=passwordConfirm", "Value={rndStr}", ENDITEM, 
		"Name=firstName", "Value={rndStr}", ENDITEM, 
		"Name=lastName", "Value={rndStr}", ENDITEM, 
		"Name=address1", "Value={rndStr}, {rndStr}, {rndStr}", ENDITEM, 
		"Name=address2", "Value={rndStr}", ENDITEM, 
		"Name=register.x", "Value=37", ENDITEM, 
		"Name=register.y", "Value=8", ENDITEM, 
		LAST);
	
	lr_end_transaction("customer_profile",LR_AUTO);
	lr_think_time(5);
	lr_start_transaction("sucsess_continue");
	
	web_reg_find("Text=Welcome, <b>{rndStr}</b>, to the Web Tours reservation pages", LAST);
	
	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("sucsess_continue",LR_AUTO);
	
	lr_end_transaction("02_RegistrationWebTours", LR_AUTO);

	return 0;
}