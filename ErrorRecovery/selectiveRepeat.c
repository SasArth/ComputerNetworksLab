#include <stdio.h>
#include <stdbool.h>

#define WINDOW_SIZE 4

typedef struct {
    int frame_no;
    bool acked;
} Frame;

void send_frames(Frame frames[], int start, int end) {
    for (int i = start; i <= end; i++) {
        printf("Sending Frame %d\n", frames[i].frame_no);
    }
}

void receive_ack(Frame frames[], int acked_frame) {
    frames[acked_frame].acked = true;
    printf("Received ACK for Frame %d\n", frames[acked_frame].frame_no);
}

int main() {
    Frame frames[WINDOW_SIZE];

    // Initialize frames
    for (int i = 0; i < WINDOW_SIZE; i++) {
        frames[i].frame_no = i + 1;
        frames[i].acked = false;
    }

    int next_to_send = 0;
    int last_acked = -1;

    while (true) {
        // Send frames
        int frames_to_send = WINDOW_SIZE - (next_to_send - last_acked);
        if (frames_to_send > 0) {
            int end = next_to_send + frames_to_send - 1;
            if (end >= WINDOW_SIZE) {
                end = WINDOW_SIZE - 1;
            }
            send_frames(frames, next_to_send, end);
            next_to_send = end + 1;
        }

        // Check for ACKs
        int ack;
        printf("Enter the ACK received: ");
        scanf("%d", &ack);

        if (ack >= 0 && ack < WINDOW_SIZE) {
            receive_ack(frames, ack);
            last_acked = ack;
        } else {
            printf("Invalid ACK\n");
        }

        // Check if all frames are acknowledged
        bool all_acked = true;
        for (int i = 0; i < WINDOW_SIZE; i++) {
            if (!frames[i].acked) {
                all_acked = false;
                break;
            }
        }

        if (all_acked) {
            break;
        }
    }

    printf("All frames acknowledged successfully.\n");

    return 0;
}
