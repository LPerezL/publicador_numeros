FROM alpine:latest AS builder
RUN apk add --no-cache build-base cmake
WORKDIR /app
COPY CMakeLists.txt main.cpp ./
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build

FROM alpine:latest
RUN apk add --no-cache netcat-openbsd libstdc++ libgcc
WORKDIR /app
COPY --from=builder /app/build/publicador /app/publicador

EXPOSE 9000

ENV WAVE_AMPLITUDE=10.0
ENV WAVE_FREQUENCY=1.0
ENV WAVE_PHASE=0.0
ENV NOISE_MEAN=0.0
ENV NOISE_STDDEV=1.5
ENV SAMPLE_RATE=50.0

CMD ["sh", "-c", "./publicador | nc -l -k 9000"]