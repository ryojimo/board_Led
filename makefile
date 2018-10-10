OBJS       = main.o \
             hal_cmnGpio.o \
             hal_led.o
TARGET     = a.out
TARGET_MAP = a.map

CFLAGS = -v -O2 -Wall -c

all                    : a.out
main.o                 : main.c
hal_cmnGpio.o          : hal_cmnGpio.c
hal_led.o              : hal_led.c


a.out: $(OBJS)
	gcc $(OBJS) -o $(TARGET) -Wl,-Map=$(TARGET_MAP)

%.o: %.c
	gcc $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET_MAP)

