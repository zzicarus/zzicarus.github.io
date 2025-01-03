![image-20241129082551201](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202411290825331.png)

## Semaphores

### no busy waiting 

![image-20241204115453459](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412041155591.png)

- **semaphores**
	- 

## Dead Lock

### Prevention

### Avoid

- state 资源分配状态
	- 
	- 已分配的
	- 进程Max的资源数

- safe sequence
	- 最初会有一种分配（Current）
	- 之后观察能否满足全都能执行
		

![image-20241204145545967](https://zzh-pic-for-self.oss-cn-hangzhou.aliyuncs.com/img/202412041455084.png)

```C
The Customers:

    wait(CHAIRS);
    wait(BUSYLOCK);
    if(left_chairs <= 0)
    {
        signal(CHAIRS);
        signal(BUSYLOCK);
        // exit
    }else{
        if(busy)
        {
            left_chairs--;
            // wait
        }
        signal(CUSTOMER);  // 保证customer < n
        signal(CHAIRS);
        signal(BUSYLOCK);
    }

The Barber:

    while(1){
        wait(CUSTOMER);  // if no customer, sleep
        
        wait(CHAIRS);
        if(left_chairs < n)
        {
            left_chairs++;
        }
        signal(CHAIRS);
        
        // cut hair

        wait(CHAIRS);
        if(left_chairs == n)
        {   // 剪完唯一的正在剪的
            wait(BUSYLOCK);
            busy = false;
            signal(BUSYLOCK);
        }
        signal(CHAIRS);
    }


int left_chairs = n;
bool busy = false;

semaphore CHAIRS = 1;
semaphore BUSYLOCK = 1;
semaphore CUSTOMER = 0;
```

