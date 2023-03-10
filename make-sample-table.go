package main

import (
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"

	wav "github.com/youpy/go-wav"
)

func main() {
	// sox conversion sox 1.wav -r 4000 -c 1 -b 8 2.wav
	// convertWavToInts("2.wav")
	convertWavToInts([]string{"0.wav"})
	// convertWavToInts([]string{"2.wav","3.wav","4.wav"})
}

func convertWavToInts(fnames []string) (err error) {
	ss:= `#ifndef SAMPLE_TABLE_H_
#define SAMPLE_TABLE_H_

#define NUM_SAMPLES XXX

const int pos[] = {
    YYY
};
const byte SAMPLE_TABLE[] PROGMEM = {
	ZZZ
};
#endif
`
_= ss
	numSamples := 0 
	sampleString := ""
	poses := []string{"0"}
	for j, fname := range fnames {
		file, _ := os.Open(fname)
		reader := wav.NewReader(file)
		n:=0
		if j>0 {
			sampleString += ",\n"
		}
		for {
			samples, err := reader.ReadSamples()
			if err == io.EOF {
				break
			}

			for i, sample := range samples {
				sampleString += fmt.Sprintf("%d", reader.IntValue(sample, 0))
				if i < len(samples)-1 {
					sampleString += ",\n"
					n++
				}
			}
		}		
		file.Close()
		numSamples += n
		poses = append(poses,fmt.Sprint(numSamples))
	}
	ss = strings.Replace(ss,"XXX",fmt.Sprint(len(fnames)),1)
	ss = strings.Replace(ss,"YYY",strings.Join(poses,","),1)
	ss = strings.Replace(ss,"ZZZ",sampleString,1)

f, _ := os.Create("generated-sample-table.h")
f.WriteString(ss)
f.Close()

	return
}

func convertIntsToWav(fname string, fout string) (err error) {
	b, err := os.ReadFile(fname)
	if err != nil {
		return
	}
	var vals []int
	for _, s := range strings.Split(string(b), ",") {
		num, errNum := strconv.Atoi(s)
		if errNum == nil {
			vals = append(vals, num)
		}
	}

	var numSamples uint32 = uint32(len(vals))
	var numChannels uint16 = 1
	var sampleRate uint32 = 4000
	var bitsPerSample uint16 = 8

	outfile, err := os.Create(fout)
	if err != nil {
		return
	}
	defer outfile.Close()

	writer := wav.NewWriter(outfile, numSamples, numChannels, sampleRate, bitsPerSample)
	samples := make([]wav.Sample, numSamples)

	for i, v := range vals {
		samples[i].Values[0] = v
	}

	err = writer.WriteSamples(samples)

	return

}
