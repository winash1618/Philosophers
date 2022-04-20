# memset
  - The C library function void *memset(void *str, int c, size_t n) copies the character c (an unsigned char) to the first n character
of the string pointed to, by the argument str.
  - Let's see an example for memset.
  ## Parameters :
  - str : This is a pointer to the block of memory to fill.
  - c : This is the value to be set. The value is passed as an int, but the function fills the block of memory using the unsigned char conversion  of this value.
  - n : This is the number of bytes to be set to the value.
  ## Return Value : 
  - This function returns a pointer to the memory area str.
  ## Sample program :
 ```
  #include <stdio.h>
  #include <string.h>

  int main () {
     char str[50];

     strcpy(str,"This is string.h library function");
     puts(str);

     memset(str,'$',7);
     puts(str);

     return(0);
  }
 ```
   ## Output : 
 ```
    This is string.h library function
    $$$$$$$ string.h library function
 ```
 
 # gettimeofday
  - The gettimeofday() function gets the system’s clock time. The current time is expressed in elapsed seconds and microseconds since 00:00:00, 
January 1, 1970 (Unix Epoch).
  - int gettimeofday ( struct timeval *tp ,  struct timezone *tz );
  ## Arguments
  - This function takes two arguments:
    - The 1st argument points to the timeval structure. The timeval structure is declared as below in sys/time.h header file :
    - The struct timeval structure represents a calendar time. It has two members:
      - tv_sec : It is the number of seconds since the epoch([what is epoch](https://www.epoch101.com/)).
      - tv_usec : It is additional microseconds after number of seconds calculation since the epoch.
    ```
      struct    timeval  {
        time_t        tv_sec ;   //used for seconds
        suseconds_t       tv_usec ;   //used for microseconds
      }
    ```
    -  The 2nd argument points to the timezone structure. It should normally be set to NULL because struct timezone is obsolete.
          This argument is for backwards compatibility only([what is backwards compatibility](https://en.wikipedia.org/wiki/Backward_compatibility/)).
    ```
        struct timezone {
          int     tz_minuteswest; /* minutes west of Greenwich */
          int     tz_dsttime;     /* type of dst correction */
        };
    ```
    - This structure contains two members relevant to time zone information: int tz_minuteswest which is the number of minutes west of GMT for the 
    system’s current time zone. Some member tz_dsttime is an integer that indicates the number of hours to adjust for daylight saving time. 
    These are time details not readily available in the other time functions.
    
  ## Return values
  - On success, the gettimeofday() return 0, for failure the function returns -1.
  ## Sample program :
  ```
    #include <stdio.h>
    #include <sys/time.h>

    int main()
    {
        struct timeval tv;
        struct timezone tz;

        gettimeofday(&tv, &tz);

        printf("Seconds since 1/1/1970: %lu\n",tv.tv_sec);
        printf("Microseconds: %d\n",tv.tv_usec);
        printf("Minutes west of Greenwich: %d\n",tz.tz_minuteswest);
        printf("Daylight Saving Time adjustment: %d\n",tz.tz_dsttime);

        return(0);
    }
  ```
  ## Output
  ```
    Seconds since 1/1/1970: 1650427445
    Microseconds: 851174
    Minutes west of Greenwich: -240
    Daylight Saving Time adjustment: 0
  ```
  
 
 
 
 
 
