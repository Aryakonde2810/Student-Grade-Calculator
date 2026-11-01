FROM gcc:14

WORKDIR /app

COPY backend/ .

RUN gcc -DMG_ENABLE_POSIX_FS=0 \
    main.c mongoose.c calculator.c \
    -o server

EXPOSE 10000

CMD ["./server"]