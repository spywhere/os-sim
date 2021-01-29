FROM alpine:3.12 AS builder

RUN mkdir -p /etc/app
WORKDIR /etc/app
COPY . /etc/app

RUN apk add --no-cache clang build-base
RUN make CC=clang++

FROM alpine:3.12
COPY --from=builder /etc/app/bin/ossim /usr/bin/ossim
RUN apk add --no-cache libstdc++
CMD /usr/bin/ossim
