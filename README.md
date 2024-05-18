# LLTpaReader

Reading the data from old LLTpa, then convert it to json file.

## Usage

Put old LLTpa data in `plugins/LLTpaReader/data`, then start your server.  
The result will be exported in `plugins/LLTpaReader/output.json`

## Output format

```jsonc
{
    "homes": {
        "xuid": {
            "home's name": {
                "dimension": 0,
                "x": 285.1832275390625,
                "y": 26.620010375976563,
                "z": -186.39068603515625
            }
        }
    },
    "warps": {
        "warp's name": {
            "dimension": 0,
            "x": -24.487401962280273,
            "y": 67.62001037597656,
            "z": -276.75738525390625
        }
    }
}
```
