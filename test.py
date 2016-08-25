class Fruit:
	price = 0
	def __init__(self):
		self.color = "red"
		zone = "China"
	def grow(self):
		print "Fruit grow..."


if __name__ == "__main__":
	print Fruit.price


directory = ["/sdb/","/sdc/","/sdd/","/sde/","/sdf/"]
#f.write("createudp 127.0.0.1  %d\n" %(PORT)) #10.7.7.28
#item = "push %s%s%d%s %d\n" % (directory[i-1],prefix, i, sufix, IDX)
# "createudp {0} {1}\n".format(self.target, self.port)
print "push %s" %(directory[0])
