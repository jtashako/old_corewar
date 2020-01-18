#!/bin/bash
#this script must be run from inside ./debug

usage() {
	echo "usage: champion_ncycle_bytestring.bash [champion.cor] [NCYCLES]"
	echo "	champion's name (not path) is expected"
	echo "	expect (12sec & 12.4MB)/ 1000cycles"
}

die() {
	#printf '%s\n' "$1" >&2
	exit "${2:-1}"
}

if [[ $# -ne 2 ]]; then
	usage
	die
fi

if [[ ! -f ../champions/$1.cor ]]; then
	echo "$1.cor does not exist in ../champions/"
	usage
	die
fi

if ! [[ "$2" =~ ^[0-9]+$ ]]; then
	echo "$2 is not an int"
	usage
	die
fi

champion=$1
N=$2 #number of mem cycles to generate

cp ../champions/$1.cor .

for i in $(seq 0 "$N"); do
	./42corewar -d "$i" "$1".cor >> "$1".mem
done

cat "$1".mem  | sed '/^Introducing.*$/d' | sed '/^.*Player.*$/d' | sed '/^.*has won.*$/d' | sed '/^.*tie.*$/d' | sed -E 's/^0x[0-9a-f]{4} : (.*)$/\1/' | tr -d ' ' | tr -d '\n' > "$1".bytestring
echo '' >> "$1".bytestring
rm "$1".mem
