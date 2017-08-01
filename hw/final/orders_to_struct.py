import sys

if len(sys.argv) == 1:
  print("Usage: %s ORDER_FILE" % (sys.argv[0]))
  sys.exit(-1)

infile = open(sys.argv[1])
lines = infile.readlines()

for line in lines:
  line = line.rstrip()

  if line[-1] == ":":
    order_num = int(line[-2])
    print("const char* order_%i[] = {" % order_num)
  else:
    print('    "%s",' % line)

  if line.strip() == "endOfOrder":
    print("    };\n");
