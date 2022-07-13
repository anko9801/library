import angr
import logging

binary_path = './chall'

target = angr.Project(binary_path, main_opts={'base_addr': 0x10000})
logging.getLogger('angr').setLevel(logging.CRITICAL)
entry_state = target.factory.entry_state()
simulation = target.factory.simulation_manager(entry_state)
simulation.explore(find=0x000115b1, avoid=0x000115c4)
for sf in simulation.found:
    print(sf.posix.dumps(0))

solution - simulation.found[0].posix.dumps(0)
print(solution)
