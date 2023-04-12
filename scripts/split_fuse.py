# split_fuse.py
#
# Splits the 3byte fuse
# into lfuse, hfuse and efuse
# to be written to a tiny461a
#
# HS 4/4/23

from intelhex import IntelHex
import argparse

parser = argparse.ArgumentParser("Splits fuse intel hex file.")

parser.add_argument('in_fuse')
parser.add_argument('outfuse_prefix')

args = parser.parse_args()

infile : str = args.in_fuse
prfx : str = args.outfuse_prefix

lfuse = prfx + "lfuse.hex"
hfuse = prfx + "hfuse.hex"
efuse = prfx + "efuse.hex"


ih = IntelHex(infile)

ih_d : dict = ih.todict()

# Split into 3
ih_l = IntelHex()
ih_h = IntelHex()
ih_e = IntelHex()

# get start
k_min = ih.minaddr() 

# Done
ih_l_dict = {0: ih_d[k_min]}
ih_h_dict = {0: ih_d[k_min+1]}
ih_e_dict = {0: ih_d[k_min+2]}

ih_l.fromdict(ih_l_dict)
ih_h.fromdict(ih_h_dict)
ih_e.fromdict(ih_e_dict)

ih_l.write_hex_file(efuse)
ih_h.write_hex_file(hfuse)
ih_e.write_hex_file(lfuse)