#!/usr/bin/awk -f

BEGIN {
	s_total = 0;
	s_passed = 0;
	s_failed = 0;
	s_skipped = 0;
	s_test = "summary"

	total = 0;
	passed = 0;
	failed = 0;
	skipped = 0;
	test = "";

	printf("%-10s%-10s%-10s%-7s  %-30s\n",
		  "total", "passed", "failed", "skipped", "test");
}

{
	passed = $2-2;
	failed = $4;
	skipped = $6;
	total = passed + failed + skipped;
	test = $9;
	printf(" %-9d %-9d %-9d %-6d   %-30s\n",
		  total, passed, failed, skipped, test);

	s_total += total;
	s_passed += passed;
	s_failed += failed;
	s_skipped += skipped;
}

END {
	printf(" %-9d %-9d %-9d %-6d   %-30s\n",
		  s_total, s_passed, s_failed, s_skipped, s_test);
}

