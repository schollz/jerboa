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
	convertIntsToWav("2.wav.txt", "3.wav")
}

func convertWavToInts(fname string) (err error) {
	file, _ := os.Open(fname)
	reader := wav.NewReader(file)

	defer file.Close()

	for {
		samples, err := reader.ReadSamples()
		if err == io.EOF {
			break
		}

		for i, sample := range samples {
			fmt.Printf("%d", reader.IntValue(sample, 0))
			if i < len(samples)-1 {
				fmt.Print(",")
			}
		}
	}

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
