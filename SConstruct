import os
def list_dir(dir):
	all_dirs = []
	for root, dirs, files in os.walk('./', True):
		for name in dirs:
			cur_dir = os.path.join(root, name)
			if cur_dir.find(".git") < 0:
				all_dirs.append(cur_dir)
	return all_dirs

obj = Glob('*.cpp')
all_dirs = list_dir('./')
print all_dirs
for dir in all_dirs:
	obj += Glob(dir + '/*.cpp')
env = Environment(CXXFLAGS="-std=c++0x") 
env.Program('xj_thread', list(obj), LIBS=['pthread'])
