# prgent usage

- create/encode barcode output for `my barcode product 1`

```sh
./prgent --mode 1 --input "my barcode product 1"
```
>or
```sh
./prgent --mode barcode-encode --input "my barcode product 1"
```

<br>

- decode barcode input from `my barcode product 1.svg`

```sh
./prgent --mode 2 --input "my barcode product 1.svg"
```
>or
```sh
./prgent --mode barcode-decode --input "my barcode product 1.svg"
```

<br>

- create/encode qrcode output for `https://mywebsite.net/home`

```sh
./prgent --mode 3 --input "https://mywebsite.net/home"
```
>or
```sh
./prgent --mode qrcode-encode --input "https://mywebsite.net/home"
```

<br>

- decode qrcode input from `https---mywebsite-net-home.svg`

```sh
./prgent --mode 4 --input "https---mywebsite-net-home.svg"
```
>or
```sh
./prgent --mode qrcode-decode --input "https---mywebsite-net-home.svg"
```

<br>

- generate 6 barcode batch & save output as csv/json and image stored as png

```sh
./prgent --mode 1 --input "my_batch_barcode" --batch-iter 6 --output-ext png --batch-out-csv true --batch-out-json true
```
>or
```sh
./prgent --mode barcode-encode --input "my_batch_barcode" --batch-iter 6 --output-ext png --batch-out-csv true --batch-out-json true
```

- generate 6 qrcode batch & save output as csv/json and image stored as png

```sh
./prgent --mode 1 --input "my_batch_barcode" --batch-iter 6 --output-ext png --batch-out-csv true --batch-out-json true
```
>or
```sh
./prgent --mode barcode-encode --input "my_batch_barcode" --batch-iter 6 --output-ext png --batch-out-csv true --batch-out-json true
```

<br>

---

###### end of prgent usage
