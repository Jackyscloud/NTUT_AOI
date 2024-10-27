flowchart TD
    Start((Start))
    Start --> A[Initialize Class SIC]
    A --> B["Input number of splits (SIC.split)"]
    B --> C["SIC.Build()"]
    C --> D["SIC.Calculate_interval_Max()"]
    D --> E["Initialize image_process (IP)"]
    E --> F["IP.create_images()"]
    F --> G["image_new = IP.image_calc(28, -30, 0)"]
    G --> H["IP.print_image(image_new)"]
    H --> I["SIC.count(image_new)"]
    I --> J["SIC.verify()"]
    J --> K["SIC.plot_counting_result()"]
    K --> End((End))
