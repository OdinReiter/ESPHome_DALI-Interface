```yaml
# example configuration:

light:
  - platform: monochrome
    output: output_1

dali:
  id: my_dali
  sending_pin: 1
  reading_pin: 2

output:
  - platform: dali
    id: output_1
    dali_id: my_dali
    address: 5
```