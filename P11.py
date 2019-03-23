import multiprocessing as mp
import time

def burnTime(k):
	t0=time.time()
	print("Hi Job %d" % k)

	time.sleep(0.25)
	print("Bye Job %d" % k)
	t1=time.time()
	return t1-t0

if __name__ == '__main__':
	pool = mp.Pool(4); # Create a pool of 4 processes

	# Apply burnTime to this list of "job numbers" using the pool
	result = pool.map(burnTime,range(10))
	print(result)
