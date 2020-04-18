# Lib Procmaps
Parsing library for the `/proc/<PID>/maps` pseudofile.
<br>

## Installation

### 1. Makefile
```sh
$> git clone https://github.com/Harmos274/libprocmaps
$> cd libprocmaps
$> mkdir build && cd build && cmake ..
$> sudo make install
```

### 2. Copying
...or just copy `include/procmaps.h` and `src/parse_procmaps.c` into your project repository!
<br>

## Documentation

```C
hr_procmaps **contruct_procmaps(int pid);
```
Parse `/proc/<PID>/maps` to create an object `hr_procmaps` containing information on the maps of the process **PID**.
The `pid` argument is the **PID** of the process to get the maps of. If it is set to 0 or a negative value, the function will parse `/proc/self/maps` instead, fetching information about itself.

```C
void destroy_procmaps(hr_procmaps **procmaps);
```
Destroy the `hr_procmaps` object freeing the allocated memory.

**Example :**
```C
#include <stdio.h>
#include <procmaps.h>

int main(void)
{
	hr_procmaps procmaps = construct_procmaps(0);
	
	printf("0x%0llx", procmaps[0]->addr_begin);
	destroy_procmaps(procmaps);
	return 0;
}
```


Refer to the [wiki](https://github.com/Harmos274/libprocmaps/wiki) for additional details.


**Enjoy !**
