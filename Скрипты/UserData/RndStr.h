RndStr(char* param_name, int length) {

char buff[32] = "";

  int r,i;
  char c;
  srand(time(NULL));

for (i = 0; i < length; i++)
{
    r = rand() % 25 + 97;
    c = (char)r;
    buff[i] = c;
    printf("%c", c);
   
}

lr_save_string(buff, param_name);
return 0;

}
