package com.imczy.googlehost.util;

import java.io.Closeable;
import java.io.IOException;

/**
 * Created by chenzhiyong on 16/4/17.
 */
public class CloseUtil {

	public static void close(Closeable closeable) {
		if (closeable != null) {
			try {
				closeable.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
