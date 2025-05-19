import cv2

# List to store clicked points
points = []

def click_event(event, x, y, flags, param):
    """Handle mouse click events: draw a red dot and print relative coords."""
    if event == cv2.EVENT_LBUTTONDOWN:
        points.append((x, y))

        # Draw a filled red circle (radius=5)
        cv2.circle(img_display, (x, y), 2, (0, 0, 255), -1)

        # Compute offset from top-right
        h, w = img.shape[:2]
        offset_x = w - x
        offset_y = y

        print(f"Clicked at ({x}, {y}) → {offset_x}px left of top‑right, {offset_y}px down")

        # Refresh display
        cv2.imshow("Image", img_display)

if __name__ == "__main__":
    # === 1. Load the image ===
    img_path = r'C:\Users\Admin\LSHADE\lab.png'  # ◀️ Replace with your file path
    img = cv2.imread(img_path)
    if img is None:
        print(f"Error: could not load '{img_path}'")
        exit(1)

    # Make a copy so we don’t redraw over the original
    img_display = img.copy()

    # === 2. Create a large, resizable window ===
    cv2.namedWindow("Image", cv2.WINDOW_NORMAL)
    # You can tweak these numbers to fill more of your screen
    cv2.resizeWindow("Image", 1200, 800)

    # === 3. Set mouse callback ===
    cv2.setMouseCallback("Image", click_event)

    # === 4. Main loop ===
    while True:
        cv2.imshow("Image", img_display)
        key = cv2.waitKey(1) & 0xFF
        if key == 27:  # ESC key to exit
            break

    cv2.destroyAllWindows()
