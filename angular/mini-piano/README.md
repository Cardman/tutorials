# MiniPiano

Les sons viennent d'un autre projet hébergé sur github.
J'ai appliqué une transformation en utilisant JMusic.

Sounds come from another project hosted on github.
I have applied a transform by using JMusic.

https://github.com/deanmalone/PianoPlay/

```
float[] audio = Read.audio("original.wav");
double rt = 1.0594630943592891448630189411239;
float[] nd = new float[(int) (audio.length / rt) + 1];
int counter = 0;
for (double i = 0.0; i < audio.length; i += rt) {
	nd[counter++] = audio[(int) i];
}
Write.audio(nd,"current.wav");
```


## Development server

## Code scaffolding

## Build

## Running unit tests

## Running end-to-end tests

## Further help

